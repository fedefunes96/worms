#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include "socket.h"
#include <thread>
#include <mutex>
#include "player.h"
#include "room.h"

class Server {
private:
	Socket skt;
	bool active_server;

	std::vector<std::unique_ptr<Player>> players;
	std::vector<Room> rooms;

	void check_active_users();
	void end_user(std::unique_ptr<Player> player);
	void end_server();

public:
	Server(const std::string& port, int cant_users);

	void interrupt_server();
	void start();
};

#endif
