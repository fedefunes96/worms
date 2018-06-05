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

void Server::check_active_users() {
	std::vector<std::unique_ptr<Player>>::iterator it;

	it = this->players.begin();

	while (it != this->players.end()) {
		if ((*it)->is_disconnected()) {
			this->end_user(std::move(*it));
			it = this->players.erase(it);
		} else {
			++it;
		}
	}

}

void Server::start() {
	this->active_server = true;

	while (this->active_server) {
		try {			
			Socket user = this->skt.aceptar();

			std::unique_ptr<Player> player(new Player(std::move(user)));

			player->start();

			this->check_active_users();

			this->players.push_back(std::move(player));
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
	std::vector<std::unique_ptr<Player>>::iterator it;

	it = this->players.begin();

	while (it != this->players.end()) {
		this->end_user(std::move(*it));
		it = this->players.erase(it);
	}	
}

void Server::interrupt_server() {
	this->active_server = false;
	//Shutdown server, stop accepting clients
	this->skt.desconectar();
}