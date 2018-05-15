#include "game.h"
#include "player.h"
#include "stage.h"
#include <vector>
#include "common_thread.h"
#include "common_socket_exception.h"
#include <algorithm>

Game::Game(Stage stage, std::vector<Player> players) 
 : stage(std::move(stage)), players(std::move(players)) {
 	this->id_actual_player = 0;
 }

void Game::run() {
	Game_status game_status = UNDEFINED;

	while (game_status == UNDEFINED) {
		Player& actual_player = this->get_actual_player();

		try {
			actual_player.play();
		} catch(const SocketException& e) {
			//Player disconnected

		}

		game_status = this->check_for_winner();

		this->round_over();
	}

	this->end_game(game_status);
}

Player& Game::get_actual_player() {
	//return *(this->players.begin() + this->id_actual_player);
	return this->players[id_actual_player];
}

void Game::notify_winner() {
	std::vector<Player>::iterator it = this->players.begin();

	while (it != this->players.end()) {
		if (!(*it).lost()) {
			//Notify winner
			Player winner = std::move(*it);
			this->players.erase(it);
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
	std::vector<Player>::iterator it = this->players.begin();

	int cant_players_alive = 0;

	while (it != this->players.end()) {
		if (!(*it).lost()) {
			cant_players_alive++;
		}
	}

	if (cant_players_alive == 1) {
		//this->winner = this->get_last_player();
		return WINNER;
	} else if (cant_players_alive == 0) {
		return DRAW;
	}

	return UNDEFINED;
}

void Game::round_over() {
	/*if (++this->id_actual_player >= (int) this->players.size()) {
		this->id_actual_player = 0;
	} else {

	}*/

	(this->id_actual_player+1 >= (int) this->players.size() 
	? this->id_actual_player = 0 : this->id_actual_player++);
}