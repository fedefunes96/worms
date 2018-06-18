#include "event_attach_worm.h"
#include "event.h"
#include "protocol.h"
#include "player.h"
#include "worm.h"

EventAttachWorm::EventAttachWorm(const int id, std::shared_ptr<Worm> worm) 
 : id(id), worm(std::move(worm)) {}

void EventAttachWorm::process(Player& player, Protocol& protocol) {	
	if (id == player.get_id()) {
		player.attach_worm(worm);
	}

	protocol.sendWormId(id, worm->get_id(), worm->get_health());
}
