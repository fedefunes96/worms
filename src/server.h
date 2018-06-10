#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include "socket.h"
#include <thread>
#include <mutex>
#include "player.h"
#include "room.h"
#include "game.h"
#include <unordered_map>

class Server {
private:
	Socket skt;
	bool active_server;

	std::unordered_map<int, std::unique_ptr<Player>> players;
	std::unordered_map<std::string, Room> rooms;
	std::vector<std::unique_ptr<Game>> games;
	std::vector<std::string> maps;

	std::mutex room_m;

	void check_active_users();
	void check_active_games();
	void end_user(std::unique_ptr<Player> player);
	void end_game(std::unique_ptr<Game> game);
	void end_server();

public:
	Server(const std::string& port, int cant_users);

	void interrupt_server();
	void start();

	std::vector<std::string> get_rooms();
	std::vector<std::string>& get_maps();
	void create_room(const int id, const std::string name, const std::string stage_file);
	void start_new_game(std::vector<int> ids, const std::string& name, const std::string stage_file);
	void join_room(const int id, const std::string& name);
	void exit_room(const int id);
};

#endif
