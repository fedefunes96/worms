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
	: protocol(protocol) {

	this->my_turn = false;
	this->continue_receiving = true;
}

bool Player::is_my_turn() {
	//mutex
	return this->my_turn;
}

void Player::set_turn() {
	//mutex
	this->my_turn = this->my_turn ? false : true;
}

int Player::get_second_counter() {
	//mutex
	return this->second_counter;
}

void Player::set_second_counter(int count) {
	//mutex
	this->second_counter = count;
}

void Player::play() {
	//Comunications:
	//1 byte - Command
	//-------
	//Command == Move
	//1 byte - Id worm (Unnecessary)
	//1 byte - Move direction
	//Command == Stop moving
	//1 byte - Id worm
	//-------
	//Command = Type of attack
	//1 byte - Id weapon (Not necessary (I have type of attack as id))
	//1 byte - Id worm
	//4 bytes - Pos X
	//4 bytes - Pos Y
	//Variable power if needed
	//1 byte - Var power
	//Countdown if needed
	//1 byte - Countdown

	/*this->set_turn();
	this->set_second_counter(60);
	this->start_counting();*/
	//Ask game for time, change
	//May happen that player disconnect's
	//So don't make other player's wait
	/*while (this->get_second_counter() > 0 && this->is_my_turn()) {
		//mutex
		//1 second
		std::thread(std::chrono(1000)):
		this->second_counter--; 
	}	
	//No longer my turn
	this->set_turn();*/
}

void Player::start_receiving() {
	while (this->continue_receiving) {
		try {
			/*
			char cmd = this->protocol.receive_cmd();

			if (!this->my_turn)
				continue;
			*/
		} catch(SocketException& e) {
			//Played disconnected
			//Throw PlayerDisconnected
			break;
		}
	}
}

/*Player::Player(Player&& other)
	: protocolo(other.protocolo)
	, usables(other.usables)
	, worms(other.worms) {
}*/

void Player::notify_actual_player(int id) {
	//Need mutex type (2)
	//Send:
	//1 byte - command notify turn
	//1 byte - player id

	//this->protocol.send(id);
}

void Player::notify_removal(Ubicable* ubicable) {
	//Need mutex type (2)
	//Send:
	//1 byte - command notify remove object
	//1 byte - type of object
	//1 byte - owner (in case of worm)
	//this->protocol.send(ubicable);
}

void Player::notify_position(Ubicable* ubicable, float x, float y, float angle) {
	//Need mutex type (2)
	//Send:
	//1 byte - command notify position object
	//1 byte - type of object
	//4 bytes - id obj
	//4 bytes - pos X
	//4 bytes - pos Y
	//4 bytes - angle

	int8_t id_type;

	if (ubicable->get_type().compare("Worm") == 0) {
		id_type = 0;
	} else if (ubicable->get_type().compare("Girder") == 0) {
		id_type = 1;
	} else if (ubicable->get_type().compare("Throwable") == 0) {
		id_type = 2;
	}

	int32_t id_obj = ubicable->get_id();

	int32_t posX = static_cast<int32_t>(x);
	int32_t posY = static_cast<int32_t>(y);
	int32_t angle_int = static_cast<int32_t>(angle);

	this->protocol.sendPosition(id_type, id_obj, posX, posY, angle_int);
}

void Player::attach_worm(std::unique_ptr<Worm>& worm) {
	this->protocol.sendWormId((char) worm->get_id(), worm->get_health());
}

void Player::attach_usable(int id, std::unique_ptr<Usable>& usable) {

}

void Player::set_id(int id) {
	this->id = id;
	//Notify client id
	this->protocol.sendPlayerId((char) id);
}

int Player::get_id() {
	return this->id;
}

bool Player::lost() {
	return false;
}