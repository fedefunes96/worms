#include "room.h"
#include <algorithm>

Room::Room(Server& server
	, const std::string stage_file
	, const int max_players)
	: server(server)
	, stage_file(stage_file)
	, max_players(max_players) {

	this->ammount_players = 0;
}

void Room::add_player(const int id) {
	this->player_ids.push_back(id);
}

bool Room::has_player(const int id) {
	if (std::find(this->player_ids.begin()
		, this->player_ids.end(), id) != this->player_ids.end())
		return true;

	return false;
}

void Room::remove_player(const int id) {
	this->player_ids.erase(
		std::remove(this->player_ids.begin(), this->player_ids.end(), id)
		, this->player_ids.end());	
}

int Room::get_ammount_players() {
	return this->ammount_players;
}