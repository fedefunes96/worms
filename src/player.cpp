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



Player::Player(Protocol protocol) 
	: protocol(std::move(protocol)) {

	this->my_turn = false;
	this->continue_receiving = true;
}

Player::Player(Player&& other)
	: protocol(std::move(other.protocol))
	, usables(std::move(other.usables))
	, worms(std::move(other.worms)) {

	this->my_turn = false;
	this->continue_receiving = true;
}

bool Player::is_my_turn() {
	std::lock_guard<std::mutex> lock(this->turn_m);

	return this->my_turn;
}

void Player::set_turn(bool state) {
	std::lock_guard<std::mutex> lock(this->turn_m);

	this->my_turn = state;
}

void Player::play() {
	this->set_turn(true);

	this->counter.set_time(20);

	this->counter.start_counting();

	printf("Starts turn of 20 secs\n");

	while (!this->counter.is_over() && this->is_my_turn()) {}

	printf("Ends turn of 20 secs\n");
	
	this->counter.stop();

	this->set_turn(false);
}

void Player::game_loop() {
	while (this->continue_receiving) {
		try {
			/*
			char cmd = this->protocol.receive_cmd();

			if (!this->my_turn)
				continue;
			*/

			Commands cmd = static_cast<Commands>(this->protocol.recvCmd());

			if (cmd == Commands::MOVE) {
				int id_worm;
				int dir;

				this->protocol.recvMove(&id, &dir);

				MoveDirection mdir = static_cast<MoveDirection>(dir);

				//Should check if worm exists
				this->worms.at(id_worm)->start_moving(mdir);

			} else if (cmd == Commands::ATTACK) {
				int id_usable;
				int id_worm;
				int posx;
				int posy;

				std::vector<float> params;

				this->protocol.recvAttack(&id_usable, &id_worm, &posx, &posy, params);    

				b2Vec2 dest(posx, posy);

				this->worms.at(id_worm)->use(this->usables.at(id_usable), dest, params);
			} else {
				//Player's cheating
				//Disconnect him
			}

			if (!this->is_my_turn())
				continue;

		} catch(SocketException& e) {
			//Played disconnected
			//Throw PlayerDisconnected
			break;
		}
	}
}

void Player::notify_winner(int id) {
	this->protocol.sendWinner(id);
}

void Player::notify_game_end() {
	//mutex
	this->continue_receiving = false;
	this->protocol.sendGameEnd();
}

void Player::notify_actual_player(int id) {

	this->protocol.sendActualPlayer(id);
}

void Player::notify_removal(Ubicable* ubicable) {

	if (ubicable->get_type().compare("Worm") == 0) {
		std::unordered_map<int, std::unique_ptr<Worm>&>::const_iterator it;

		it = this->worms.find(ubicable->get_id());

		if (it != this->worms.end()) {
			this->worms.erase(it);
		}
	}

	this->protocol.sendRemove(ubicable->get_type(), ubicable->get_id());
}

void Player::notify_position(Ubicable* ubicable, float x, float y, float angle) {

	this->protocol.sendPosition(ubicable->get_type(), ubicable->get_id(), x, y, angle);
}

void Player::attach_worm(std::unique_ptr<Worm>& worm) {

	this->worms.emplace(worm->get_id(), worm);
	this->protocol.sendWormId(worm->get_id(), worm->get_health());
}

void Player::attach_usable(std::unique_ptr<Usable> usable) {

	this->usables.emplace(usable->get_id(), std::move(usable));
	this->protocol.sendUsableId(usable->get_id(), usable->get_ammo());
}

void Player::set_id(int id) {
	this->id = id;
	//Notify client id
	this->protocol.sendPlayerId(id);
}

int Player::get_id() {
	return this->id;
}

bool Player::lost() {
	//need mutex
	return this->worms.size() == 0;
}