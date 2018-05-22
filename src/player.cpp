#include "usable.h"
#include "worm.h"
#include <unordered_map>
#include "player.h"
#include <memory>
#include "protocol.h"
#include "ubicable.h"
#include <thread>
#include "common_socket_exception.h"

Player::Player(const int id
	, Protocol protocol
	, std::unordered_map<int, std::unique_ptr<Usable>&> usables
	, std::unordered_map<int, Worm> worms) 
	: id(id)
	, protocol(protocol)
	, usables(std::move(usables))
	, worms(std::move(worms)) {

	//this->protocol.send(this->id)
}

void Player::play() {
	//Comunications:
	//1 byte - Command
	//-------
	//Command == Move
	//1 byte - Id worm
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
	bool turn_over = false;

	std::thread wait_t(&Player::wait_to_play, this, 60, &turn_over);

	while (!turn_over) {
		try {
			//char cmd = this->protocol.receive_command();

			//PlayerCmdCreator cmd_creator;

			//Consider 0 == Move
			// ""      1 == Attack
			/*if (cmd == 0) {

			}*/
		} catch (SocketException& e) {
			//Make all players wait?
			//Destroy thread or another method to wait
			wait_t.join();
			turn_over = true;
		}
	}

	wait_t.join();
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

void Player::notify_position(Ubicable* ubicable, float x, float y) {
	//Need mutex type (2)
	//Send:
	//1 byte - command notify position object
	//1 byte - type of object
	//4 bytes - pos X
	//4 bytes - pos Y
	//4 bytes - health (in case of worm)
	//this->protocol.send(ubicable, x, y);
}

bool Player::lost() {
	return false;
}