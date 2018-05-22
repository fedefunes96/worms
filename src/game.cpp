#include "game.h"
#include "player.h"
#include "stage.h"
#include <vector>
#include "common_thread.h"
#include "common_socket_exception.h"
#include <algorithm>
#include <thread>

Game::Game(std::vector<Player> players) 
 : stage(1.0/60.0, 6, 2, *this) 
 , players(std::move(players)) {
 	this->id_actual_player = 0;

 	this->initialize_game();

 	//Start drawing the stage
 	//this->stage_t = std::thread(&Stage::draw, &this->stage);
}

void Game::initialize_game() {
	/*std::vector<Player>::iterator it;

	for (it = players.begin(); it != players.end(); ++it) {

	}*/
}

void Game::run() {
	Game_status game_status = UNDEFINED;

	while (game_status == UNDEFINED) {
		Player& actual_player = this->get_actual_player();

		try {
			//Notify everyone whose turn it is
			this->notify_actual_player(this->id_actual_player);

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
	//return *(this->players.begin() + this->id_actual_player);
	return this->players[this->id_actual_player];
}

void Game::notify_winner() {
	//std::unordered_map<int, Player>::iterator it = this->players.begin();
	std::vector<Player>::iterator it = this->players.begin();

	while (it != this->players.end()) {
		if (!(*it).lost()) {
			//Notify winner
			//Player winner = std::move(*it);
			break;
		}
	}	
}

void Game::end_game(Game_status game_status) {
	/*if (game_status == WINNER) {
		//Show message "Winner" to winner
		this->notify_winner();
	}*/
	this->notify_winner();
	//Show message "Loser" to all losers
	//this->notify_losers();
}

Game_status Game::check_for_winner() {
	//std::unordered_map<int, Player>::iterator it = this->players.begin();
	std::vector<Player>::iterator it = this->players.begin();

	int cant_players_alive = 0;

	while (it != this->players.end()) {
		if (!(*it).lost()) {
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

	Game_status game_status = check_for_winner();

	(this->id_actual_player+1 >= (int) this->players.size() 
	? this->id_actual_player = 0 : ++this->id_actual_player);

	return game_status;
}

void Game::notify_actual_player(int id) {
	std::vector<Player>::iterator it;

	for (it = this->players.begin(); it != this->players.end(); ++it) {
		(*it).notify_actual_player(id);
	}
}

void Game::notify_position(Ubicable* ubicable, float x, float y) {
	std::vector<Player>::iterator it;

	for (it = this->players.begin(); it != this->players.end(); ++it) {
		(*it).notify_position(ubicable, x, y);
	}
}

void Game::notify_removal(Ubicable* ubicable) {
	std::vector<Player>::iterator it;

	for (it = this->players.begin(); it != this->players.end(); ++it) {
		(*it).notify_removal(ubicable);
	}
}

Game::~Game() {
	//Must place something to stop drawing
	//this->stage_t.join();
}