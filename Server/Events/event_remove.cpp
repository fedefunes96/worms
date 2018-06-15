#include "event_remove.h"
#include "event.h"
#include "protocol.h"
#include "player.h"
#include <iostream>

EventRemove::EventRemove(const std::string type, const int id)
	: type(type), id(id) {}

void EventRemove::process(Player& player, Protocol& protocol) {
	printf("Sending Remove object:");
	std::cout << type << " " << id << std::endl;
	protocol.sendRemove(type, id);
}
