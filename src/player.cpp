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

Player::Player(Socket socket) 
	: socket(std::move(socket))
	, protocol(this->socket) {

	this->should_receive = true;
	this->connected = true;
}

Player::Player(Player&& other)
	: socket(std::move(other.socket))
	, protocol(this->socket)
	, usables(std::move(other.usables))
	, worms(std::move(other.worms)) {

	this->should_receive = other.should_receive;
	this->connected = other.connected;
}

bool Player::should_i_receive() {
	std::lock_guard<std::mutex> lock(this->turn_m);

	return this->should_receive;
}

void Player::set_receive(bool state) {
	std::lock_guard<std::mutex> lock(this->turn_m);

	this->should_receive = state;
}

void Player::play() {
	this->set_receive(true);

	this->counter.set_time(40);

	printf("Starts turn of 40 secs\n");

	this->counter.start_counting();

	printf("Ends turn of 40 secs\n");

	this->set_receive(false);
}

void Player::run() {
	this->game_loop();
}

void Player::game_loop() {
	try {
		while (this->connected) {	
			Commands cmd = static_cast<Commands>(this->protocol.recvCmd());

			if (cmd == Commands::MOVE) {
				int id_worm;
				int dir;

				this->protocol.recvMove(&id, &dir);

				MoveDirection mdir = static_cast<MoveDirection>(dir);

				//Should check if worm exists
				std::lock_guard<std::mutex> lock(this->worms_m);
				this->worms.at(id_worm)->start_moving(mdir);

			} else if (cmd == Commands::ATTACK) {
				int id_usable;
				int id_worm;
				int posx;
				int posy;

				std::vector<float> params;

				this->protocol.recvAttack(&id_usable, &id_worm, &posx, &posy, params);    

				b2Vec2 dest(posx, posy);

				std::lock_guard<std::mutex> lock(this->worms_m);
				this->worms.at(id_worm)->use(this->usables.at(id_usable), dest, params);
			} else {
				//Player's cheating
				//Disconnect him
				this->disconnected_player();
				this->connected = false;
			}

			if (!this->should_i_receive())
				continue;

			//std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		}
	} catch(SocketException& e) {
			//Played disconnected
			this->disconnected_player();
			this->connected = false;
	}
}

void Player::disconnected_player() {
	//Remove each of his worms
	//std::lock_guard<std::mutex> lock(this->worms_m);

	this->set_receive(false);

	std::unordered_map<int, std::shared_ptr<Worm>>::iterator it;

	while (it != this->worms.end()) {
		it->second->force_death();

		//it = this->worms.erase(it);

		++it;
	}
}

void Player::check_if_worm_was_mine(Ubicable* ubicable) {
	std::lock_guard<std::mutex> lock(this->worms_m);

	std::unordered_map<int, std::shared_ptr<Worm>>::const_iterator it;

	it = this->worms.find(ubicable->get_id());

	if (it != this->worms.end()) {
		this->worms.erase(it);
	}
}

void Player::notify_winner(int id) {
	printf("Sending Winner\n");
	this->protocol.sendWinner(id);
}

void Player::notify_game_end() {
	//mutex
	printf("Sending Game end\n");
	this->protocol.sendGameEnd();
	this->connected = false;
}

void Player::notify_actual_player(int id) {

	printf("Actual Player id: %d\n", id);
	this->protocol.sendActualPlayer(id);
}

void Player::notify_removal(Ubicable* ubicable) {
	/*if (ubicable->get_type().compare("Worm") == 0) {
		this->check_if_worm_was_mine(ubicable);
	}*/

	printf("Sending Remove object\n");
	this->protocol.sendRemove(ubicable->get_type(), ubicable->get_id());
}

void Player::notify_position(Ubicable* ubicable, float x, float y, float angle) {
	if ((ubicable->get_type()).compare("Worm")==0) {
		//printf("Sending Position worm: %0.1f %0.1f %0.1f\n", x, y, angle);	
	}
	this->protocol.sendPosition(ubicable->get_type(), ubicable->get_id(), x, y, angle);
}

//void Player::attach_worm(Worm* worm) {
void Player::attach_worm(std::shared_ptr<Worm> worm) {
	printf("Sending Worm id: %d %d\n", worm->get_id(), worm->get_health());
	this->worms.emplace(worm->get_id(), worm);
	this->protocol.sendWormId(worm->get_id(), worm->get_health());
}

void Player::attach_usable(std::unique_ptr<Usable> usable) {
	printf("Sending Usable id: %d %d\n", usable->get_id(), usable->get_ammo());
	this->protocol.sendUsableId(usable->get_id(), usable->get_ammo());
	this->usables.emplace(usable->get_id(), std::move(usable));
}

void Player::set_id(int id) {
	this->id = id;
	printf("Sending Player id: %d\n", id);
	//Notify client id
	this->protocol.sendPlayerId(id);
}

int Player::get_id() {
	return this->id;
}

bool Player::lost() {
	//std::lock_guard<std::mutex> lock(this->worms_m);

	std::unordered_map<int, std::shared_ptr<Worm>>::const_iterator it;

	it = this->worms.begin();

	if (it != this->worms.end()) {
		if(!it->second->im_dead())
			return false;

		++it;
	}	

	return true;
	//return this->worms.size() == 0;
}

bool Player::is_disconnected() {
	return this->connected == 0;
}