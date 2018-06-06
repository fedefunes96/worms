#include "server.h"
#include <string>
#include <vector>
#include "socket.h"
#include <thread>
#include <mutex>
#include "player.h"
#include "common_socket_exception.h"

Server::Server(const std::string& port, int cant_users)
 : skt(port, cant_users) {
 	active_server = false;
}

void Server::end_user(std::unique_ptr<Player> player) {
	player->join();
}

void Server::end_game(std::unique_ptr<Game> game) {
	game->join();
}

void Server::check_active_users() {
	std::unordered_map<int, std::unique_ptr<Player>>::iterator it;

	it = this->players.begin();

	while (it != this->players.end()) {
		if (it->second->is_disconnected()) {
			this->end_user(std::move(it->second));
			it = this->players.erase(it);
		} else {
			++it;
		}
	}
}

void Server::check_active_games() {
	std::vector<std::unique_ptr<Game>>::iterator it;

	it = this->games.begin();

	while (it != this->games.end()) {
		if ((*it)->game_finished()) {
			this->end_game(std::move(*it));
			it = this->games.erase(it);
		} else {
			++it;
		}
	}
}

void Server::start() {
	int id = 0;
	this->active_server = true;

	while (this->active_server) {
		try {			
			Socket user = this->skt.aceptar();

			std::unique_ptr<Player> player(new Player(std::move(user)));

			player->start();

			this->check_active_users();
			this->check_active_games();

			this->players.emplace(id, std::move(player));

			id++;
		} catch(SocketException& e) {
			//Problem with an user
			//Continue accepting new users
			//Or server stopped
		}
	}

	this->end_server();
}

void Server::end_server() {
	//Wait for every game to end
	//And disconnect every player that is not playing
	std::unordered_map<int, std::unique_ptr<Player>>::iterator it;

	it = this->players.begin();

	while (it != this->players.end()) {
		this->end_user(std::move(it->second));
		it = this->players.erase(it);
	}	

	std::vector<std::unique_ptr<Game>>::iterator it_g; 

	it_g = this->games.begin();

	while (it_g != this->games.end()) {
		this->end_game(std::move((*it_g)));
		it_g = this->games.erase(it_g);
	}
}

void Server::interrupt_server() {
	this->active_server = false;
	//Shutdown server, stop accepting clients
	this->skt.desconectar();
}