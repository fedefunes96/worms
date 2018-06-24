#include "event_show_rooms.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"

EventShowRooms::EventShowRooms(const std::vector<std::string> rooms) 
 : rooms(std::move(rooms)) {}

void EventShowRooms::process(Player& player, ProtocolServer& protocol) {
	printf("Se enviaron las salas\n");
	protocol.sendRooms(rooms);
}
