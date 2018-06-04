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

Game::Game(const std::string& stage_file, std::vector<Player> players) 
 : stage(stage_file, 1.0/60.0, 6, 2, *this) 
 , players(std::move(players)) {
 	this->id_player_list = 0;

 	this->initialize_players();
 	this->initialize_game(stage_file);
 	this->start_game();
}

void Game::start_game() {
	printf("Creating threads\n");
	this->stage_t = std::thread(&Stage::draw, &this->stage);
	//this->game_t = std::thread(&Game::game_loop, this);

	for (int i = 0; i < (int) this->players.size(); i++) {
		this->players_t.push_back(
			std::thread(&Player::game_loop, &this->players[i])
		);
	}

	this->game_loop();
	//printf("Waiting 20 secs to end game\n");
	//std::this_thread::sleep_for(std::chrono::milliseconds(20000));
	//printf("Game ended 20 secs\n");

	//this->stage.stop_drawing();
}

void Game::initialize_players() {
	//First, set an id to every player
	//Starting with id = 1
	for (int i = 0; i < (int) this->players.size(); i++) {
		this->players[i].set_id(i+1);
	}
}

void Game::create_test_world() {
	//Let's create 2 worms
	Worm* worm = new Worm(this->stage
		, 10 //10 x right
		, 3 // 20 y up
		, 0.0 // Angle 0 -> Facing right
		, 1 //Long 2m long
		, 1 //Height 2m height
		, 0.0 //Bouncing null
		, 100.0 //100 hp
		, 2.0 //Mov speeed
		, std::make_pair (10.0,20.0) //Forw jump
		, std::make_pair (10.0,20.0) //Back jump
		, 10.0);

	std::shared_ptr<Worm> worm1_ptr = std::shared_ptr<Worm>(worm);
	//Copy the shared ptr
	this->players[0].attach_worm(worm1_ptr);

	//Move the shared ptr (faster)
	this->stage.insert(std::move(worm1_ptr));
	//this->stage.insert(std::shared_ptr<Movable>(worm));

	Worm* worm2 = new Worm(this->stage
		, 5 //5 x right
		, 10 // 10 y up
		, 0.0 // Angle 0 -> Facing right
		, 1 //Long 2m long
		, 1 //Height 2m height
		, 0.0 //Bouncing null
		, 100.0 //100 hp
		, 2.0 //Mov speeed
		, std::make_pair (10.0,20.0) //Forw jump
		, std::make_pair (10.0,20.0) //Back jump
		, 10.0);

	std::shared_ptr<Worm> worm2_ptr = std::shared_ptr<Worm>(worm2);

	this->players[0].attach_worm(worm2_ptr);
	this->stage.insert(std::move(worm2_ptr));
	//this->stage.insert(std::shared_ptr<Movable>(worm2));

	std::unique_ptr<Usable> ptr = std::unique_ptr<Usable>(new Bazooka(this->stage, INFINITY_AMMO));	

	//this->players[0].attach_worm(worm);
	//this->players[0].attach_worm(worm2);
	this->players[0].attach_usable(std::move(ptr));

	//Create 3 girders

	this->stage.insert(
		std::unique_ptr<Ubicable>(new Girder(this->stage
		, 0
		, 0
		, b2_pi/2 //Vertical
		, 20
		, 1)));

	this->stage.insert(
	std::unique_ptr<Ubicable>(new Girder(this->stage
		, 20
		, 0
		, b2_pi
		, 20
		, 1)));

	this->stage.insert(
	std::unique_ptr<Ubicable>(new Girder(this->stage
		, 0
		, 0
		, 0.0
		, 200
		, 1)));
}

void Game::initialize_game(const std::string& stage_file) {
	this->create_test_world();
	//First, create every object in the stage

	//Read stage and create ubicables
	//Push them in a list to mantain them


	//Reserve a list with a reference to worms & usables
	//std::vector<Worms&> worms_to_attach
	//std::vector<std::unique_ptr<Usable&>> usables_to_attach

	//int cant_worms = worms_to_attach.size()
	//int cant_players = this->players.size()

	// if (cant_players > cant_worms)
	//		invalid_game

	//int remu_worms = (cant_worms % cant_players);
	//int worms_per_player = cant_worms / cant_players;
	//int players_with_less_worms = cant_players - remu_worms
	/*
	int i;
	int j = 0;

	//Attach now to players that will have less worms
	//Give extra health to the worms
	for (i = 0; i < players_with_less_worms; i++) {
		for (; j < worms_per_player*(i+1); j++) {
			Worm& worm = worms_to_attach[j];
			worm.add_health(EXTRA_HEALTH);
			this->players[i].attach_worm(std::move(worm));
		}
	}

	//Attach now to players that will have more worms
	for (; i < cant_players; i++) {
		for (; j < worms_to_attach*(i+1)+1; j++) {
			Worm& worm = worms_to_attach[j];
			this->players[i].attach_worm(std::move(worm));
		}		
	}

	*/
}

void Game::game_loop() {
	Game_status game_status = UNDEFINED;

	while (game_status == UNDEFINED) {
		Player& actual_player = this->get_actual_player();

		try {
			//Notify everyone whose turn it is
			this->notify_actual_player(actual_player.get_id());

			actual_player.play();
		} catch(const SocketException& e) {
			//Player disconnected

		}
		//Need conditional variable over Stage
		game_status = this->round_over();

	}

	this->end_game(game_status);
}

Player& Game::get_actual_player() {
	return this->players[this->id_player_list];
}

void Game::notify_winner() {
	int id_winner;

	for (int i = 0; i < (int) this->players.size(); i++) {
		if (!this->players[i].lost()) {
			id_winner = this->players[i].get_id();
			break;
		}
	}

	for (int i = 0; i < (int) this->players.size(); i++) {
		this->players[i].notify_winner(id_winner);
	}
}

void Game::end_game(Game_status game_status) {
	/*if (game_status == WINNER) {
		//Show message "Winner" to winner
		this->notify_winner();
	}*/
	this->notify_winner();
	//printf("Game ended\n");
	//Show message "Loser" to all losers
	//this->notify_losers();
}

Game_status Game::check_for_winner() {
	int cant_players_alive = 0;

	for (int i = 0; i < (int) this->players.size(); i++) {
		if (!this->players[i].lost()) {
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

Game_status Game::round_over() {

	printf("Round is over!\n");

	Game_status game_status = check_for_winner();

	(this->id_player_list+1 >= (int) this->players.size() 
	? this->id_player_list = 0 : ++this->id_player_list);

	return game_status;
}

void Game::notify_actual_player(int id) {
	std::vector<Player>::iterator it;

	for (it = this->players.begin(); it != this->players.end(); ++it) {
		(*it).notify_actual_player(id);
	}
}

void Game::notify_position(Ubicable* ubicable, float x, float y, float angle) {
	std::vector<Player>::iterator it;

	for (it = this->players.begin(); it != this->players.end(); ++it) {
		(*it).notify_position(ubicable, x, y, angle);
	}
}

void Game::notify_removal(Ubicable* ubicable) {
	std::vector<Player>::iterator it;

	for (it = this->players.begin(); it != this->players.end(); ++it) {
		(*it).notify_removal(ubicable);
	}
}

float Game::get_water_level() {
	return this->water.get_water_level();
}

Game::~Game() {
	//for (int i = 0; i < this->players.size(); i++)
	//	this->players.join();

	this->stage.stop_drawing();
	this->stage_t.join();
	//this->game_t.join();

	for (int i = 0; i < (int) this->players.size(); i++) {
		this->players[i].notify_game_end();
		
		this->players_t[i].join();
	}

	/*for (int i = 0; i < (int) this->players_t.size(); i++) {
		this->players_t[i].join();
	}*/
}