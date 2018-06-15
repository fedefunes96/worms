#include "event_start_game.h"
#include "event.h"
#include "protocol.h"
#include "player.h"

EventStartGame::EventStartGame() {}

void EventStartGame::process(Player& player, Protocol& protocol) {
	printf("Se envio empezar juego\n");
	protocol.sendStartGame();
}
