#include "event_worm_status.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"
#include <algorithm>

EventWormStatus::EventWormStatus(const int id, bool ground, MoveDirection dir)
	: id(id), ground(ground), dir(dir) {}

void EventWormStatus::process(Player& player, ProtocolServer& protocol) {
	protocol.sendWormStatus(id, ground, static_cast<int>(dir));
}
