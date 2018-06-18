#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>

class Server;

class Room {
private:
	Server& server;
	const std::string name;
	const std::string stage_file;
	const int max_players;
	std::vector<int> player_ids;

public:
	Room(Server& server
		, const std::string name
		, const std::string stage_file
		, const int max_players);

	void add_player(const int id);
	bool has_player(const int id);
	void remove_player(const int id);	
	std::vector<int>& get_players_ids();
};

#endif
