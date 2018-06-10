#include "event_start_game.h"
#include "event.h"
#include "protocol.h"
#include "player.h"

EventStartGame::EventStartGame() {}

void EventStartGame::process(Player& player, Protocol& protocol) {
	protocol.sendStartGame();
}
