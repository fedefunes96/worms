#include "event_players_in_room.h"
#include "event.h"
#include "protocol.h"
#include "player.h"
#include <iostream>

EventPlayersInRoom::EventPlayersInRoom(const int size)
	: size(size) {}

void EventPlayersInRoom::process(Player& player, Protocol& protocol) {
	printf("size %i\n",size );
	protocol.sendPlayersInRoom(size);
}
