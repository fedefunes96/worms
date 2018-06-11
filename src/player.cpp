#include "usable.h"
#include "worm.h"
#include <unordered_map>
#include "player.h"
#include <memory>
#include "protocol.h"
#include "ubicable.h"
#include <thread>
#include <string>
#include "common_socket_exception.h"
#include "server.h"

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

	printf("Sending player id: %d\n", id);
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
	/*this->new_worm_id();
	int actual_worm = this->get_actual_worm();

	while (this->worms.at(actual_worm).im_dead()) {
		this->new_worm_id();
		actual_worm = this->get_actual_worm();		
	}

	this->protocol.sendActualWorm(actual_worm);*/

	this->can_attack = true;
	this->set_receive(true);

	this->counter.set_time(10);

	printf("Starts turn of 40 secs\n");

	this->counter.start_counting();

	printf("Ends turn of 40 secs\n");

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
			Commands cmd = static_cast<Commands>(this->protocol.recvCmd());

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
 
				//this->counter.set_time(3);
				this->counter.set_time(15);

				printf("Usable id %d\n", id_usable);
 
 				std::lock_guard<std::mutex> lock(this->worms_m);
 				this->worms.at(this->get_actual_worm())->use(this->usables.at(id_usable), dest, std::move(params));

			} else if (cmd == Commands::SHOW_ROOMS) {
				std::vector<std::string> rooms_name = this->server.get_rooms();
				
				this->protocol.sendRooms(rooms_name);

			} else if (cmd == Commands::JOIN_ROOM) {
				std::string room_name;

				this->protocol.recvRoom(room_name);

				this->server.join_room(this->get_id(), room_name);
			
			} else if (cmd == Commands::CREATE_ROOM) {
				std::string room_name;
				std::string stage_file;

				this->protocol.recvCreateRoom(room_name, stage_file);

				this->server.create_room(this->get_id(), room_name, stage_file);

			} else if (cmd == Commands::MAP_LIST) {
				std::vector<std::string> maps = this->server.get_maps();

				this->protocol.sendMaps(maps);

			} else if (cmd == Commands::EXIT_ROOM) {
				this->server.exit_room(this->get_id());

			} else {
				//Player's cheating
				//Disconnect him
				this->disconnected_player();
			}

			if (!this->should_i_receive())
				continue;
			//std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		}
	} catch(SocketException& e) {
			//Played disconnected
			this->disconnected_player();
	}

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
	//Remove each of his worms
	//std::lock_guard<std::mutex> lock(this->worms_m);
	this->set_receive(false);
		
	if (this->is_in_game()) {
		//Stop counter if it was my turn
		this->counter.stop();

		std::unordered_map<int, std::shared_ptr<Worm>>::iterator it;

		it = this->worms.begin();

		while (it != this->worms.end()) {
			printf("Killing worm id: %d\n", it->second->get_id());
			it->second->force_death();

			//it = this->worms.erase(it);

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
/*void Player::notify_start_game() {
	this->in_game = true;
	this->protocol.sendGameStart();
}*/

void Player::notify_winner(int id) {
	printf("Sending Winner\n");
	//this->protocol.sendWinner(id);
}

void Player::disconnect() {
	//mutex
	//printf("Sending Game end\n");
	//this->protocol.sendGameEnd();
	//this->connected = false;
	//Do this in other place, server might eliminate player while sending msj disconnect
	//this->in_game = false;
	//this->event_t.join();
	//printf("Connected = false\n");
	//Put this in an event called Disconnect
	//this->socket.desconectar();
}

void Player::set_connected(bool state) {
	this->connected = state;
}

void Player::stop_events() {
	this->event_t.join();
	//this->in_game = false;
}

void Player::shutdown() {
	this->socket.desconectar();
	this->in_game = false;
}

void Player::notify_actual_player(int id) {
	printf("Actual Player id: %d\n", id);
	//this->protocol.sendActualPlayer(id);
}

void Player::notify_health(Worm* worm) {
	//this->protocol.sendWormHealth(worm->get_id(), worm->get_health());
}

void Player::notify_removal(Ubicable* ubicable) {
	/*if (ubicable->get_type().compare("Worm") == 0) {
		this->check_if_worm_was_mine(ubicable);
	}*/

	printf("Sending Remove object\n");
	//this->protocol.sendRemove(ubicable->get_type(), ubicable->get_id());
}

void Player::notify_position(Ubicable* ubicable, float x, float y, float angle) {
	if ((ubicable->get_type()).compare("Worm")==0) {
		//printf("Sending Position worm: %0.1f %0.1f %0.1f\n", x, y, angle);	
	}
	//this->protocol.sendPosition(ubicable->get_type(), ubicable->get_id(), x, y, angle);
}

//void Player::attach_worm(Worm* worm) {
void Player::attach_worm(std::shared_ptr<Worm> worm) {
	this->worms_ids.push_back(worm->get_id());

	printf("Sending Worm id: %d %d\n", worm->get_id(), worm->get_health());
	this->worms.emplace(worm->get_id(), worm);
	//this->protocol.sendWormId(worm->get_id(), worm->get_health());
}

void Player::attach_usable(std::unique_ptr<Usable> usable) {
	printf("Sending Usable id: %d %d\n", usable->get_id(), usable->get_ammo());
	//this->protocol.sendUsableId(usable->get_id(), usable->get_ammo());
	this->usables.emplace(usable->get_id(), std::move(usable));
}

void Player::set_id(int id) {
	this->id = id;
	printf("Sending Player id: %d\n", id);
	//Notify client id
	//this->protocol.sendPlayerId(id);
}

int Player::get_id() {
	return this->id;
}

bool Player::lost() {
	//std::lock_guard<std::mutex> lock(this->worms_m);

	std::unordered_map<int, std::shared_ptr<Worm>>::const_iterator it;

	it = this->worms.begin();

	if (it != this->worms.end()) {
		if(!it->second->im_dead()) {
			printf("Worm alive\n");
			return false;
		}

		++it;
	}	

	return true;
	//return this->worms.size() == 0;
}

bool Player::is_disconnected() {
	return this->connected == 0;
}

std::unordered_map<int, std::unique_ptr<Usable>>& Player::get_usables() {
	return this->usables;
}
	
std::unordered_map<int, std::shared_ptr<Worm>>& Player::get_worms() {
	return this->worms;
}

std::vector<int>& Player::get_worms_ids() {
	return this->worms_ids;
}
