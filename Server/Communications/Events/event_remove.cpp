#include "event_remove.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"
#include <iostream>

EventRemove::EventRemove(const std::string type, const int id)
	: type(type), id(id) {}

void EventRemove::process(Player& player, ProtocolServer& protocol) {
	protocol.sendRemove(type, id);
}
