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
#include "event_queue.h"

#define CANT_PLAYERS 50

int main(int argc, char* argv[]) {
	std::string port("7777");

	Socket server(port, 50);

	Socket skt = server.aceptar();

	std::vector<Player*> players;

	//Protocol protocol(skt);

	Player player(std::move(skt), 1);

	std::vector<EventQueue*> event_queues;

	event_queues.push_back(player.get_event_queue());

	//players.push_back(std::move(player));

	players.push_back(&player);

	printf("Creating a game\n");

	Game game("hi", std::move(players), event_queues);

	return 0;
}
