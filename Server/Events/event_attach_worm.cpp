#include "event_attach_worm.h"
#include "event.h"
#include "protocol.h"
#include "player.h"
#include "worm.h"

EventAttachWorm::EventAttachWorm(const int id, std::shared_ptr<Worm> worm) 
 : id(id), worm(std::move(worm)) {}

void EventAttachWorm::process(Player& player, Protocol& protocol) {
	printf("Sending Worm id: %d %d %d\n", id, worm->get_id(), worm->get_health());
	
	if (id == player.get_id()) {

		player.get_worms_ids().push_back(worm->get_id());

		player.get_worms().emplace(worm->get_id(), worm);
	}

	protocol.sendWormId(id, worm->get_id(), worm->get_health());

	//printf("Rompe\n");
}
