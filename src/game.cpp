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

#define EXTRA_HEALTH 100

Game::Game(const std::string& stage_file
 , std::vector<Player*> players
 , std::vector<EventQueue*> event_queues) 
 : players(std::move(players))
 , event_queues(std::move(event_queues))
 , stage(stage_file, 1.0/20.0, 6, 2, *this, this->event_queues) {
 	this->id_player_list = 0;
 	this->is_over = false;

 	//Remove this, use run when creating game
 	this->initialize_players();
 	this->initialize_game(stage_file);
 	this->start_game();
}

void Game::start_game() {
	printf("Creating threads\n");
	this->stage_t = std::thread(&Stage::draw, &this->stage);
	//this->game_t = std::thread(&Game::game_loop, this);

	/*for (int i = 0; i < (int) this->players.size(); i++) {
		this->players_t.push_back(
			std::thread(&Player::game_loop, this->players[i])
		);
	}*/

	this->game_loop();
	//printf("Waiting 20 secs to end game\n");
	//std::this_thread::sleep_for(std::chrono::milliseconds(20000));
	//printf("Game ended 20 secs\n");

	//this->stage.stop_drawing();
}

void Game::initialize_players() {
	//First, set an id to every player
	//Starting with id = 1
	/*for (int i = 0; i < (int) this->players.size(); i++) {
		this->players[i].set_id(i+1);
	}*/
}

void Game::initialize_game(const std::string& stage_file) {
	//First, create every object in the stage

	//Read stage and create ubicables
	//Push them in a list to mantain them


	//Reserve a list with a reference to worms & usables
	std::vector<Worm*> worms_to_attach;
	std::string map = "../yaml/basico.yaml";
	std::string config =  "../yaml/config.yaml";
	
	int waterLvl = Parser::waterLvl(config);
	float airMin = Parser::airMinSpeed(config);
	float airMax = Parser::airMaxSpeed(config);

	stage.set_wind(airMin,airMax);
	stage.set_water(waterLvl);

	Parser::loadWorms(map,config,worms_to_attach,this->stage,this);
	int cant_worms = worms_to_attach.size();
	int cant_players = this->players.size();

	// if (cant_players > cant_worms)
	//		invalid_game

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
	this->game_loop();
}

bool Game::game_finished() {
	return this->is_over;
}

void Game::game_loop() {
	Game_status game_status = UNDEFINED;
	this->is_over = false;

	while (game_status == UNDEFINED) {
		Player* actual_player = this->get_actual_player();

		try {
			//Notify everyone whose turn it is
			this->notify_actual_player(actual_player->get_id());

			actual_player->play();
		} catch(const SocketException& e) {
			//Player disconnected
		}
		//Need conditional variable over Stage

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
	/*if (game_status == WINNER) {
		//Show message "Winner" to winner
		this->notify_winner();
	}*/
	this->notify_winner();
	this->is_over = true;
	this->stage.stop_drawing();
	this->stage_t.join();
	printf("Game ended\n");
	//Show message "Loser" to all losers
	//this->notify_losers();
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

	printf("Round is over!\n");

	Game_status game_status = check_for_winner();

	if (game_status == UNDEFINED) {
		do {
			this->new_player();
		} while (this->get_actual_player()->lost());
	}

	return game_status;
}

void Game::notify_health(Worm* worm) {
	/*std::vector<Player>::iterator it;

	for (it = this->players.begin(); it != this->players.end(); ++it) {
		(*it).notify_health(worm);
	}*/
	std::shared_ptr<Event> event(new EventWormHealth(worm->get_id(), worm->get_health()));

	for (int i = 0; i < (int) this->event_queues.size(); i++) {
		this->event_queues[i]->add_event(event);
	}
}

void Game::notify_actual_player(int id) {
	/*std::vector<Player>::iterator it;

	for (it = this->players.begin(); it != this->players.end(); ++it) {
		(*it).notify_actual_player(id);
	}*/
	std::shared_ptr<Event> event(new EventActualPlayer(id));

	for (int i = 0; i < (int) this->event_queues.size(); i++) {
		this->event_queues[i]->add_event(event);
	}
}

void Game::notify_position(Ubicable* ubicable, float x, float y, float angle) {
/*	std::vector<Player>::iterator it;

	for (it = this->players.begin(); it != this->players.end(); ++it) {
		(*it).notify_position(ubicable, x, y, angle);
	}*/
}

void Game::notify_removal(Ubicable* ubicable) {
	/*std::vector<Player>::iterator it;

	for (it = this->players.begin(); it != this->players.end(); ++it) {
		(*it).notify_removal(ubicable);
	}*/
}

Game::~Game() {
	//for (int i = 0; i < this->players.size(); i++)
	//	this->players.join();

	/*this->stage.stop_drawing();
	this->stage_t.join();*/
	//this->game_t.join();
	//std::shared_ptr<Event> event(new EventDisconnect());

	/*for (int i = 0; i < (int) this->players.size(); i++) {
		this->players[i]->disconnect();
		this->event_queues[i]->add_event(event);
		//printf("add disconnect event\n");
		//this->players[i].get_event_queue()->add_event(event);
		//printf("stop event\n");
		this->players[i]->stop_events();

		this->players_t[i].join();
	}*/

	/*for (int i = 0; i < (int) this->players_t.size(); i++) {
		this->players_t[i].join();
	}*/
}
