#include "event_players_in_room.h"
#include "event.h"
#include "protocol.h"
#include "player.h"

EventPlayersInRoom::EventPlayersInRoom(const int size)
	: size(size) {}

void EventPlayersInRoom::process(Player& player, Protocol& protocol) {
	//printf("Sending position\n");

	protocol.sendPlayersInRoom(size);
}
