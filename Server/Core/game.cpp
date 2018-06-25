#include "game.h"
#include "player.h"
#include "stage.h"
#include <vector>
#include "thread.h"
#include "common_socket_exception.h"
#include <algorithm>
#include <thread>
#include <string>
#include "water.h"
#include <memory>

#include "girder.h"
#include "worm.h"
#include "bazooka.h"
#include "mortar.h"
#include "dynamite.h"
#include "parser.h"
#include "event_queue.h"
#include "event_attach_worm.h"
#include "event_attach_usable.h"
#include "event.h"
#include "event_winner.h"
#include "event_worm_health.h"
#include "event_actual_player.h"
#include "event_disconnect.h"
#include "event_worm_status.h"
#include "event_wind_speed.h"
#include "event_wind_params.h"

#define EXTRA_HEALTH 25

Game::Game(const std::string& stage_file
 , std::vector<Player*> players
 , std::vector<EventQueue*> event_queues) 
 : players(std::move(players))
 , event_queues(std::move(event_queues))
 , stage(stage_file, 1.0/20.0, 6, 2, *this, this->event_queues) {
 	this->id_player_list = 0;
 	this->is_over = false;
 	this->stage_file= stage_file; 	
}

void Game::start_game() {
	this->stage_t = std::thread(&Stage::draw, &this->stage);

	this->game_loop();
}

void Game::initialize_game(const std::string& stage_file) {
	//First, create every object in the stage

	//Read stage and create ubicables
	//Push them in a list to mantain them

	//Reserve a list with a reference to worms & usables
	std::vector<Worm*> worms_to_attach;
	std::string map = stage_file;
	std::string config =  std::string(ROOT_PATH)+"/config/config.yaml";
	
	int waterLvl = Parser::waterLvl(config);
	float airMin = Parser::airMinSpeed(config);
	float airMax = Parser::airMaxSpeed(config);

	std::shared_ptr<Event> event_windpar(new EventWindParams(airMin, airMax));

	for (int i = 0; i < (int) this->event_queues.size(); i++) {
		this->event_queues[i]->add_event(event_windpar);
	}

	stage.set_wind(airMin,airMax);
	stage.set_water(waterLvl);

	Parser::loadWorms(map,config,worms_to_attach,this->stage,this);
	int cant_worms = worms_to_attach.size();
	int cant_players = this->players.size();

	int remu_worms = (cant_worms % cant_players);
	int worms_per_player = cant_worms / cant_players;
	int players_with_less_worms = cant_players - remu_worms;
	
	int i;
	int j = 0;

	//Attach now to players that will have less worms
	//Give extra health to the worms
	for (i = 0; i < players_with_less_worms; i++) {
		for (; j < worms_per_player*(i+1); j++) {
			Worm* worm = worms_to_attach[j];
			if (remu_worms > 0){
				worm->add_health(EXTRA_HEALTH);
			}
			std::shared_ptr<Worm> worm_ptr = std::shared_ptr<Worm>(worm);
			//this->players[i].attach_worm(worm_ptr);
			
			std::shared_ptr<Event> event(new EventAttachWorm(this->players[i]->get_id(), worm_ptr));

			//Send event to everyone
			for (int k = 0; k < (int) this->event_queues.size(); k++)
				this->event_queues[k]->add_event(event);

			this->stage.insert(std::move(worm_ptr));
		}
	}

	//Attach now to players that will have more worms
	for (; i < cant_players; i++) {
		for (; j < worms_per_player*(i+1)+1; j++) {
			std::shared_ptr<Worm> worm_ptr = std::shared_ptr<Worm>(worms_to_attach[j]);
			//this->players[i].attach_worm(worm_ptr);
			std::shared_ptr<Event> event(new EventAttachWorm(this->players[i]->get_id(), worm_ptr));

			//Send event to everyone
			for (int k = 0; k < (int) this->event_queues.size(); k++)
				this->event_queues[k]->add_event(event);

			this->stage.insert(std::move(worm_ptr));
		}	
	}
	std::vector<Ubicable*> girders;
	Parser::loadGirder(map,config,this->stage,girders);
	for (unsigned int i = 0; i < girders.size();++i){
		this->stage.insert(std::unique_ptr<Ubicable>(girders[i]));
	}


	for (int i = 0; i < cant_players; ++i){
		std::vector<Usable*> usables;
		Parser::loadWeapon(map,config,stage,usables);
		for (unsigned int j = 0; j< usables.size(); ++j){
			//this->players[i].attach_usable(std::move(std::unique_ptr<Usable>(usables[j])));

			std::shared_ptr<Event> event(new EventAttachUsable(std::move(std::unique_ptr<Usable>(usables[j]))));

			//Its one event unique per player
			this->event_queues[i]->add_event(std::move(event));
		}
	}
}

void Game::run() {
 	this->initialize_game(this->stage_file);
 	this->start_game();
}

bool Game::game_finished() {
	return this->is_over;
}

void Game::game_loop() {
	Game_status game_status = UNDEFINED;
	this->is_over = false;

	while (game_status == UNDEFINED) {
		std::shared_ptr<Event> event(new EventWindSpeed(this->stage.get_wind_speed()));

		for (int i = 0; i < (int) this->event_queues.size(); i++) {
			this->event_queues[i]->add_event(event);
		}	

		Player* actual_player = this->get_actual_player();

		try {
			//Notify everyone whose turn it is
			this->notify_actual_player(actual_player->get_id(), actual_player->get_actual_worm_id());

			actual_player->play();
		} catch(const SocketException& e) {
			//Player disconnected
		}
		this->stage.wait_stop_moving();

		game_status = this->round_over();

	}

	this->end_game(game_status);
}

Player* Game::get_actual_player() {
	return this->players[this->id_player_list];
}

void Game::notify_winner() {
	int id_winner = 0;

	for (int i = 0; i < (int) this->players.size(); i++) {
		if (!this->players[i]->lost()) {
			id_winner = this->players[i]->get_id();
			break;
		}
	}

	/*for (int i = 0; i < (int) this->players.size(); i++) {
		this->players[i].notify_winner(id_winner);
	}*/
 	std::shared_ptr<Event> event(new EventWinner(id_winner));

	for (int i = 0; i < (int) this->event_queues.size(); i++) {
		this->event_queues[i]->add_event(event);
	} 	
}

void Game::end_game(Game_status game_status) {
	this->notify_winner();
	this->is_over = true;
	this->stage.stop_drawing();
	this->stage_t.join();
}

Game_status Game::check_for_winner() {
	int cant_players_alive = 0;

	for (int i = 0; i < (int) this->players.size(); i++) {
		if (!this->players[i]->lost()) {
			cant_players_alive++;
		}
	}

	if (cant_players_alive == 1) {
		return WINNER;
	} else if (cant_players_alive == 0) {
		return DRAW;
	}

	return UNDEFINED;
}

void Game::new_player() {
		if (this->id_player_list+1 >= (int) this->players.size()) {
			this->id_player_list = 0;
		} else {
			this->id_player_list++;
		}
}

Game_status Game::round_over() {

	Game_status game_status = check_for_winner();

	if (game_status == UNDEFINED) {
		do {
			this->new_player();
		} while (this->get_actual_player()->lost());

		this->stage.random_wind();
	}

	return game_status;
}

void Game::notify_health(Worm* worm) {
	std::shared_ptr<Event> event(new EventWormHealth(worm->get_id(), worm->get_health()));

	for (int i = 0; i < (int) this->event_queues.size(); i++) {
		this->event_queues[i]->add_event(event);
	}
}

void Game::notify_actual_player(const int id, const int worm_id) {
	std::shared_ptr<Event> event(new EventActualPlayer(id, worm_id));

	for (int i = 0; i < (int) this->event_queues.size(); i++) {
		this->event_queues[i]->add_event(event);
	}
}


void Game::notify_worm_status(int id, bool ground, MoveDirection facing_direction) {
	std::shared_ptr<Event> event(new EventWormStatus(id, ground, facing_direction));

	for (int i = 0; i < (int) this->event_queues.size(); i++) {
		this->event_queues[i]->add_event(event);
	}
}

Game::~Game() {}
