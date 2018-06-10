#include "event_worm_health.h"
#include "event.h"
#include "protocol.h"
#include "player.h"
#include <algorithm>

EventWormHealth::EventWormHealth(const int id, const int health)
	: id(id), health(health) {}

void EventWormHealth::process(Player& player, Protocol& protocol) {
	printf("Sending new health: %d %d\n", id, health);
	protocol.sendWormHealth(id, health);

	if (player.should_i_receive() && id == player.get_actual_worm()) {
		//Im receiving, so its my turn
		player.get_worms_ids();

		if (std::find(player.get_worms_ids().begin()
			, player.get_worms_ids().end()
			, player.get_actual_worm()) != player.get_worms_ids().end()) {
			printf("Damaging myself\n");
			player.stop_turn();
		}
	}
}
