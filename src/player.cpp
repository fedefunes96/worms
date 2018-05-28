#include "usable.h"
#include "worm.h"
#include <unordered_map>
#include "player.h"
#include <memory>
#include "protocol.h"
#include "ubicable.h"
#include <thread>
#include <string>

//#include "common_socket_exception.h"



Player::Player(Protocol protocol) 
	: protocol(protocol) {

	//this->protocol.send(this->id)
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

	/*char cmd = this->protocolo.receive_char();

	CommandCreator cmd_creator;

	std::unique_ptr<Command> command = cmd_creator.create(cmd, protocolo);

	command.execute(this->usables, this->worms);
	command.execute(this);*/
	//bool turn_over = false;

	/*std::thread wait_t(&Player::wait_to_play, this, 60, &turn_over);

	while (!turn_over) {
		try {
			//char cmd = this->protocol.receive_command();

			//PlayerCmdCreator cmd_creator;

			//Consider 0 == Move
			// ""      1 == Attack
			if (cmd == 0) {
				Worm& worm = this->worms.at(this->id_actual_worm)
				MoveDirection mdirect = this->protocol.receive_int()
				worm.start_moving(mdirect)
			}
		} catch (SocketException& e) {
			//Make all players wait?
			//Destroy thread or another method to wait
			wait_t.join();
			turn_over = true;
		}
	}

	wait_t.join();*/
}

void Player::wait_to_play(int time, bool* end) {
	//Make wait time with chrono

	*end = true;
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