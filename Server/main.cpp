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

#define CANT_PLAYERS 100
#define TERMINAR_SERVIDOR "q"
#define PARAM_SERVER 1

int main(int argc, char* argv[]) {
	if (argc == PARAM_SERVER + 1) {		
		Server server(std::string(argv[1]), CANT_PLAYERS);

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

		t.join();	
	}

	return 0;
}
