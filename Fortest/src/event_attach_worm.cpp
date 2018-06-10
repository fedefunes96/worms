#include "event_attach_worm.h"
#include "event.h"
#include "protocol.h"
#include "player.h"
#include "worm.h"

EventAttachWorm::EventAttachWorm(std::shared_ptr<Worm> worm) 
 : worm(std::move(worm)) {}

void EventAttachWorm::process(Player& player, Protocol& protocol) {
	player.get_worms_ids().push_back(worm->get_id());

	printf("Sending Worm id: %d %d\n", worm->get_id(), worm->get_health());
	player.get_worms().emplace(worm->get_id(), worm);
	//protocol.sendWormId(worm->get_id(), worm->get_health());

	//printf("Rompe\n");
}
