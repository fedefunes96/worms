#include "event_players_in_room.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"
#include <iostream>

EventPlayersInRoom::EventPlayersInRoom(const int size)
	: size(size) {}

void EventPlayersInRoom::process(Player& player, ProtocolServer& protocol) {
	printf("size %i\n",size );
	protocol.sendPlayersInRoom(size);
}
