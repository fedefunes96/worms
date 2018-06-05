#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>
#include "player.h"

class Room {
private:
	//std::vector<std::unique_ptr<Player>&> players;

public:
	Room(const std::string name
		, const std::string stage_file
		, const int cant_players);

	//void add_player(std::unique_ptr<Player>&> player);
	//void remove_player(std::unique_ptr<Player>&> player);
};

#endif
