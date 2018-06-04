#include <iostream>
#include "stage.h"
//#include "movable.h"
//#include "static.h"
#include "girder.h"
#include "throwable.h"
#include <Box2D/Box2D.h>
#include <chrono>
#include <thread>
#include "contact_listener.h"
#include "game.h"
#include "socket.h"
#include "protocol.h"

#include "counter.h"

int main(int argc, char* argv[]) {
	std::string port("7777");

	Socket server(port);

	Socket* skt = server.server_aceptar_clt();

	if (skt == nullptr)
		return 0;

	//Socket* skt = nullptr;

	std::vector<Player> players;

	Protocol protocol(skt);

	Player player(std::move(protocol));

	players.push_back(std::move(player));

	printf("Creating a game\n");

	Game game("hi", std::move(players));

	delete skt;

	return 0;
}
