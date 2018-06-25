#include "event_could_join_room.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"
#include "worm.h"

EventCouldJoinRoom::EventCouldJoinRoom(const bool could) 
 : could(could) {}

void EventCouldJoinRoom::process(Player& player, ProtocolServer& protocol) {
	protocol.sendCouldJoinRoom(could);
}
