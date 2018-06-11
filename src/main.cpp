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
#include "server.h"
#include "counter.h"
#include "event_queue.h"

#define CANT_PLAYERS 50
#define TERMINAR_SERVIDOR "q"

int main(int argc, char* argv[]) {
	std::string port("7777");

	Server serv("8888", 50);

	Socket server(port, 50);

	Socket skt = server.aceptar();

	std::vector<Player*> players;

	//Protocol protocol(skt);

	Player player(serv, std::move(skt), 1);

	std::vector<EventQueue*> event_queues;

	event_queues.push_back(player.get_event_queue());

	//players.push_back(std::move(player));

	players.push_back(&player);

	printf("Creating a game\n");

	Game game("hi", std::move(players), std::move(event_queues));

	//LO DE ARRIBA ES LO VIEJO

	/*Server server("7777", 50);

	bool esperar_quit = true;

	std::thread t(&Server::start, &server);

	while(esperar_quit) {
		std::string input;
		std::cin >> input;

		if (!input.compare("q")) {
			server.interrupt_server();
			esperar_quit = false;
		}
	}

	t.join();	*/
	return 0;
}
