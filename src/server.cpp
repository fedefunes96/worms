#include "server.h"
#include <string>
#include <vector>
#include "socket.h"
#include <thread>
#include <mutex>
#include "player.h"
#include "common_socket_exception.h"
#include "event_queue.h"
#include "event_disconnect.h"
#include "event_could_join_room.h"
#include "event_start_game.h"
#include "event_players_in_room.h"

Server::Server(const std::string& port, int cant_users)
 : skt(port, cant_users) {
 	active_server = false;

 	//Load maps in here
 	this->maps.emplace("asd","../yaml/basic.yaml");
}

void Server::end_user(std::unique_ptr<Player> player) {
	//Add event disconnect
	std::shared_ptr<Event> event(new EventDisconnect());

	player->get_event_queue()->add_event(event);	
	player->stop_events();
	player->join();
}

void Server::end_game(std::unique_ptr<Game> game) {
	//printf("Destroying game bef\n");
	//game->join();
	//printf("Destroying game\n");
}

void Server::check_active_users() {
	std::lock_guard<std::mutex> lock(this->disconnect_m);

	std::unordered_map<int, std::unique_ptr<Player>>::iterator it;

	it = this->players.begin();

	while (it != this->players.end()) {
		if (it->second->is_disconnected() && !it->second->is_in_game()) {
			printf("Player disconnected, removing from room\n");
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

			std::unique_ptr<Player> player(new Player(*this, std::move(user), id));

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
	std::lock_guard<std::mutex> lock(this->disconnect_m);

	std::vector<std::unique_ptr<Game>>::iterator it_g; 

	it_g = this->games.begin();
	while (it_g != this->games.end()) {
		this->end_game(std::move((*it_g)));
		it_g = this->games.erase(it_g);
	}


	std::unordered_map<int, std::unique_ptr<Player>>::iterator it;

	it = this->players.begin();

	while (it != this->players.end()) {
		this->end_user(std::move(it->second));
		it = this->players.erase(it);
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

std::vector<std::string> Server::get_maps() {
	std::vector<std::string> map_names;

	std::unordered_map<std::string, std::string>::iterator it;

	it = this->maps.begin();

	while (it != this->maps.end()) {
		map_names.push_back(it->first);
		++it;
	}

	return std::move(map_names);	
	//return this->maps;
}

void Server::create_room(const int id, const std::string name, const std::string stage_file) {
	this->check_active_users();

	std::lock_guard<std::mutex> lock(this->room_m);

	//Don't create a room if it already exists one
	//with it's name
	std::unordered_map<std::string, Room>::iterator it;

	it = this->rooms.find(name);

	if (it == this->rooms.end()) {
		//Read stage file and get ammount of players
		int ammount_players = 2;
		//Room room(*this, name, stage_file, ammount_players);
		Room room(*this, name, maps.at(stage_file), ammount_players);

		room.add_player(id);

		this->rooms.emplace(name, std::move(room));

		/*std::shared_ptr<Event> event_join(new EventCouldJoinRoom(true));
		this->players.at(id)->get_event_queue()->add_event(std::move(event_join));	*/	
	} else {
		/*std::shared_ptr<Event> event_join(new EventCouldJoinRoom(False));
		this->players.at(id)->get_event_queue()->add_event(std::move(event_join));	*/			
	}
}

void Server::join_room(const int id, const std::string& name) {
	this->check_active_users();

	//Join room if it can
	std::lock_guard<std::mutex> lock(this->room_m);

	std::unordered_map<std::string, Room>::iterator it;

	it = this->rooms.find(name);

	if (it != this->rooms.end()) {
		//Add event bool could join
		std::shared_ptr<Event> event_join(new EventCouldJoinRoom(true));
		this->players.at(id)->get_event_queue()->add_event(std::move(event_join));
		//For each player in room
		//Send new ammount of players

		std::vector<int> ids = it->second.get_players_ids();

		std::shared_ptr<Event> event(new EventPlayersInRoom(ids.size()+1));

		for (int i = 0; i < (int) ids.size(); i++) {
			this->players.at(ids[i])->get_event_queue()->add_event(event);
		}
		//Send him too
		this->players.at(id)->get_event_queue()->add_event(event);

		it->second.add_player(id);
	}else{
		std::shared_ptr<Event> event_join(new EventCouldJoinRoom(false));
		this->players.at(id)->get_event_queue()->add_event(std::move(event_join));
	}

	
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
			printf("Player removed\n");
			if (it->second.get_players_ids().size() == 0) {
				printf("Remove empty room\n");
				this->rooms.erase(it);
			} else {
				
				std::vector<int> ids = it->second.get_players_ids();
				std::shared_ptr<Event> event(new EventPlayersInRoom(ids.size()));

				for (int i = 0; i < (int) ids.size(); i++) {
					this->players.at(ids[i])->get_event_queue()->add_event(event);
				}			
			}

			break;
		}
		++it;
	}
}

void Server::start_new_game(std::vector<int> ids, const std::string& name, const std::string stage_file) {
	std::lock_guard<std::mutex> lock(this->disconnect_m);
	printf("start new game\n");
	std::unordered_map<std::string, Room>::iterator it;

	it = this->rooms.find(name);

	if (it != this->rooms.end()) {
		this->rooms.erase(it);

		std::vector<Player*> players_for_game;
		std::vector<EventQueue*> event_queues;

		std::shared_ptr<Event> event(new EventStartGame());

		for (int i = 0; i < (int) ids.size(); i++) {
			//Player* a = this->players.at(i).get();
			printf("id :%i\n",ids[i]);
			Player* player = this->players.at(ids[i]).get();
			player->set_in_game(true);
			player->set_receive(false);
			players_for_game.push_back(player);

			EventQueue* queue = player->get_event_queue();
			queue->add_event(event);
			event_queues.push_back(queue);
		}

		printf("10 seconds before launching game\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		printf("Launching game\n");
		this->games.push_back(std::unique_ptr<Game>(new Game(stage_file 
			, std::move(players_for_game)
			, std::move(event_queues))));
	}	
}
