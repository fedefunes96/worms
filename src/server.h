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

	void check_active_users();
	void check_active_games();
	void end_user(std::unique_ptr<Player> player);
	void end_game(std::unique_ptr<Game> game);
	void end_server();

public:
	Server(const std::string& port, int cant_users);

	void interrupt_server();
	void start();
};

#endif
