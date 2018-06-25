#include "usable.h"
#include "worm.h"
#include <unordered_map>
#include "player.h"
#include <memory>
#include "protocol_server.h"
#include "ubicable.h"
#include <thread>
#include <string>
#include "common_socket_exception.h"
#include "server.h"
#include "event_show_rooms.h"
#include "event_show_maps.h"

Player::Player(Server& server, Socket socket, const int id) 
	: server(server)
	, socket(std::move(socket))
	, protocol(this->socket) {

	this->should_receive = true;
	this->connected = true;
	this->in_game = false;
	this->id = id;
	this->id_actual_worm = 0;
	this->can_attack = false;

	this->protocol.sendPlayerId(id);

	this->event_t = std::thread(&Player::process_events, this);
}

Player::Player(Player&& other)
	: server(other.server)
	, socket(std::move(other.socket))
	, protocol(this->socket)
	, usables(std::move(other.usables))
	, worms(std::move(other.worms))
	, worms_ids(std::move(other.worms_ids))
	, event_queue(std::move(other.event_queue)) {

	this->id = other.id;
	this->should_receive = other.should_receive;
	this->connected = other.connected;
	this->in_game = other.in_game;
 	this->event_t = std::move(other.event_t);
	this->id_actual_worm = other.id_actual_worm;
	this->can_attack = other.can_attack;
}

bool Player::should_i_receive() {
	std::lock_guard<std::mutex> lock(this->turn_m);

	return this->should_receive;
}

void Player::set_receive(bool state) {
	std::lock_guard<std::mutex> lock(this->turn_m);

	this->should_receive = state;
}

void Player::new_worm_id() {
	if (this->id_actual_worm + 1 >= (int) this->worms_ids.size()) {
		this->id_actual_worm = 0;
	} else {
		this->id_actual_worm++;
	}	
}

void Player::play() {
	this->can_attack = true;
	this->set_receive(true);

	this->counter.set_time(TIME_TURN);

	this->counter.start_counting();

	this->set_receive(false);
	//Stop his worm from moving
	this->worms.at(this->get_actual_worm())->start_moving(MoveDirection::NONE);
}

void Player::stop_turn() {
	this->counter.stop();
}

void Player::run() {
	this->game_loop();
}

void Player::game_loop() {
	try {
		while (this->connected) {	
			Commands cmd = static_cast<Commands>(this->protocol.recv_char());

			if (cmd == Commands::MOVE) {
				int dir = 0;

				this->protocol.recvMove(&dir);

				if (!this->should_i_receive())
					continue;

				MoveDirection mdir = static_cast<MoveDirection>(dir);

				//Should check if worm exists
				std::lock_guard<std::mutex> lock(this->worms_m);
				this->worms.at(this->get_actual_worm())->start_moving(mdir);
			} else if (cmd == Commands::ATTACK) {
				int id_usable = 0;
				int posx = 0;
				int posy = 0;

				std::vector<int> params;

				this->protocol.recvAttack(&id_usable, &posx, &posy, params);  

				if (!this->should_i_receive())
					continue;

				if (!this->can_attack)
					continue;

				this->can_attack = false;

 				b2Vec2 dest(posx, posy);
 
				this->counter.set_time(TIME_AFTER_ATTACK);
 
 				std::lock_guard<std::mutex> lock(this->worms_m);
 				this->worms.at(this->get_actual_worm())->use(this->usables.at(id_usable), dest, std::move(params));
			} else if (cmd == Commands::SHOW_ROOMS) {
				std::vector<std::string> rooms_name = this->server.get_rooms();

				if (!this->should_i_receive())
					continue;

				//this->protocol.sendRooms(rooms_name);

				std::shared_ptr<Event> event(new EventShowRooms(std::move(rooms_name)));
				this->event_queue.add_event(std::move(event));
			} else if (cmd == Commands::JOIN_ROOM) {
				std::string room_name;

				this->protocol.recvRoom(room_name);

				if (!this->should_i_receive())
					continue;

				this->server.join_room(this->get_id(), room_name);
			} else if (cmd == Commands::CREATE_ROOM) {
				std::string room_name;
				std::string stage_file;

				this->protocol.recvCreateRoom(room_name, stage_file);

				if (!this->should_i_receive())
					continue;

				this->server.create_room(this->get_id(), room_name, stage_file);
			} else if (cmd == Commands::MAP_LIST) {
				if (!this->should_i_receive())
					continue;

				std::vector<std::string> maps = this->server.get_maps();

				//this->protocol.sendMaps(maps);
				std::shared_ptr<Event> event(new EventShowMaps(std::move(maps)));
				this->event_queue.add_event(std::move(event));
			} else if (cmd == Commands::EXIT_ROOM) {
				if (!this->should_i_receive())
					continue;

				this->server.exit_room(this->get_id());
			} else {
				//Player's cheating
				//Disconnect him
				this->disconnected_player();
			}
		}
	} catch(SocketException& e) {
			//Played disconnected
			this->disconnected_player();
	}
}

int Player::get_actual_worm_id() {
	this->new_worm_id();
	int actual_worm = this->get_actual_worm();

	while (this->worms.at(actual_worm)->im_dead()) {
		this->new_worm_id();
		actual_worm = this->get_actual_worm();		
	}

	return actual_worm;
}

int Player::get_actual_worm() {
	return this->worms_ids[this->id_actual_worm];
}

EventQueue* Player::get_event_queue() {
	return &this->event_queue;
}

void Player::process_events() {
	while (this->connected) {
		try {
			std::shared_ptr<Event> event = this->event_queue.get_event();

			event->process(*this, this->protocol);
		} catch(SocketException& e) {
			//this->connected = false;
			this->disconnected_player();
		}
	}
}

void Player::disconnected_player() {
	this->set_receive(false);
		
	if (this->is_in_game()) {
		//Stop counter if it was my turn
		this->counter.stop();

		std::unordered_map<int, std::shared_ptr<Worm>>::iterator it;

		it = this->worms.begin();

		while (it != this->worms.end()) {
			it->second->force_death();

			++it;
		}
	}

	this->connected = false;
}

bool Player::is_in_game() {
	return this->in_game;
}
void Player::set_in_game(bool state) {
	this->in_game = state;
}

void Player::set_connected(bool state) {
	this->connected = state;
}

void Player::stop_events() {
	this->event_t.join();
}

void Player::shutdown() {
	this->connected = false;
	this->socket.desconectar();
	this->in_game = false;
}

void Player::attach_worm(std::shared_ptr<Worm> worm) {
	this->worms_ids.push_back(worm->get_id());
	this->worms.emplace(worm->get_id(), worm);
}

void Player::attach_usable(std::unique_ptr<Usable> usable) {
	this->usables.emplace(usable->get_id(), std::move(usable));
}

int Player::get_id() {
	return this->id;
}

bool Player::lost() {
	for (auto it = this->worms.begin(); it != this->worms.end(); ++it) {
		if(!it->second->im_dead()) {
			return false;
		}		
	}

	return true;
}

bool Player::is_disconnected() {
	return this->connected == 0;
}
