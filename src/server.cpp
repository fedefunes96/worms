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

 	//Load maps in here
}

void Server::end_user(std::unique_ptr<Player> player) {
	player->join();
}

void Server::end_game(std::unique_ptr<Game> game) {
	game->join();
}

void Server::check_active_users() {
	//Dont disconnect players that are trying to initialize game
	std::lock_guard<std::mutex> lock(this->room_m);

	std::unordered_map<int, std::unique_ptr<Player>>::iterator it;

	it = this->players.begin();

	while (it != this->players.end()) {
		if (it->second->is_disconnected() && !it->second->is_in_game()) {
			this->exit_room(it->first);
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

			//Remove those users
			this->check_active_users();
		} else {
			++it;
		}
	}
}

void Server::start() {
	int id = 1;
	this->active_server = true;

	while (this->active_server) {
		try {			
			Socket user = this->skt.aceptar();

			std::unique_ptr<Player> player(new Player(std::move(user), id));

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

std::vector<std::string> Server::get_rooms() {
	std::lock_guard<std::mutex> lock(this->room_m);

	std::vector<std::string> rooms_names;

	std::unordered_map<std::string, Room>::iterator it;

	it = this->rooms.begin();

	while (it != this->rooms.end()) {
		rooms_names.push_back(it->first);
		++it;
	}

	return std::move(rooms_names);
}

std::vector<std::string>& Server::get_maps() {
	return this->maps;
}

void Server::create_room(const int id, const std::string name, const std::string stage_file) {
	std::lock_guard<std::mutex> lock(this->room_m);
	//Read stage file and get ammount of players
	int ammount_players = 2;

	Room room(*this, stage_file, ammount_players);

	room.add_player(id);

	this->rooms.emplace(name, std::move(room));
}

void Server::join_room(const int id, const std::string& name) {
	//Join room if it can
	std::lock_guard<std::mutex> lock(this->room_m);

	std::unordered_map<std::string, Room>::iterator it;

	it = this->rooms.find(name);

	if (it != this->rooms.end()) {
		it->second.add_player(id);
		//Add event bool could join
		//this->players[id].sendCouldJoin(true);
		//For each player in room
		//Send new ammount of players
		//return true;		
		//return true;
	}

	//return false;
}

void Server::exit_room(const int id) {
	//Exit room if it can
	std::lock_guard<std::mutex> lock(this->room_m);

	std::unordered_map<std::string, Room>::iterator it;

	it = this->rooms.begin();

	while (it != this->rooms.end()) {
		if (it->second.has_player(id)) {
			it->second.remove_player(id);

			//No players left in the room
			//Remove it
			if (it->second.get_ammount_players() == 0) {
				this->rooms.erase(it);
			}

			break;
		}
		++it;
	}
}

void Server::start_new_game(std::vector<int> ids, const std::string& name, const std::string stage_file) {
	std::lock_guard<std::mutex> lock(this->room_m);

	std::unordered_map<std::string, Room>::iterator it;

	it = this->rooms.find(name);

	if (it != this->rooms.end()) {
		this->rooms.erase(it);

		std::vector<Player*> players_for_game;

		for (int i = 0; i < (int) ids.size(); i++) {
			//Player* a = this->players.at(i).get();
			players_for_game.push_back(this->players.at(i).get());
		}

		//this->games.push_back(std::unique_ptr<Game>(new Game(stage_file, players_for_game)))
	}	
}
