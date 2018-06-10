#include "room.h"
#include <algorithm>
#include "server.h"

Room::Room(Server& server
	, const std::string name
	, const std::string stage_file
	, const int max_players)
	: server(server)
	, name(name)
	, stage_file(stage_file)
	, max_players(max_players) {
}

void Room::add_player(const int id) {
	this->player_ids.push_back(id);

	if ((int) this->player_ids.size() == max_players) {
		server.start_new_game(std::move(this->player_ids)
			, this->name
			, this->stage_file);
	}
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

std::vector<int>& Room::get_players_ids() {
	return this->player_ids;
}
