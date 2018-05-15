#include "usable.h"
#include "worm.h"
#include <unordered_map>
#include "player.h"
#include <memory>
#include "protocolo.h"

Player::Player(Protocolo protocolo
	, std::unordered_map<int, std::unique_ptr<Usable>&> usables
	, std::unordered_map<int, Worm> worms) 
	: protocolo(protocolo)
	, usables(std::move(usables))
	, worms(std::move(worms)) {

}

void Player::play() {
	//Comunications:
	//1 byte - Command
	//-------
	//Command == Move
	//1 byte - Id worm
	//1 byte - Move direction
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
}

/*Player::Player(Player&& other)
	: protocolo(other.protocolo)
	, usables(other.usables)
	, worms(other.worms) {
}*/

bool Player::lost() {
	return false;
}