#include "event_remove.h"
#include "event.h"
#include "protocol.h"
#include "player.h"

EventRemove::EventRemove(const std::string type, const int id)
	: type(type), id(id) {}

void EventRemove::process(Player& player, Protocol& protocol) {
	printf("Sending Remove object\n");
	protocol.sendRemove(type, id);
}
