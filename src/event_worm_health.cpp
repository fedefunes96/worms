#include "event_worm_health.h"
#include "event.h"
#include "protocol.h"
#include "player.h"

EventWormHealth::EventWormHealth(const int id, const int health)
	: id(id), health(health) {}

void EventWormHealth::process(Player& player, Protocol& protocol) {
	printf("Sending new health: %d %d\n", id, health);
	//protocol.sendWormHealth(id, health);
}
