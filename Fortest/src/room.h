#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>
//#include "player.h"

class Server;

class Room {
private:
	Server& server;
	const std::string stage_file;
	const int max_players;
	int ammount_players;

	//std::vector<std::unique_ptr<Player>>& players;
	std::vector<int> player_ids;

public:
	Room(Server& server
		, const std::string stage_file
		, const int max_players);

	void add_player(const int id);
	bool has_player(const int id);
	void remove_player(const int id);	
	int get_ammount_players();

	//void add_player(std::unique_ptr<Player>& player);
	//void remove_player(std::unique_ptr<Player>&> player);
};

#endif
