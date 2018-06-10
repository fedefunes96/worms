#include "event_attach_usable.h"
#include "event.h"
#include "protocol.h"
#include "player.h"
#include "worm.h"

EventAttachUsable::EventAttachUsable(std::unique_ptr<Usable> usable) 
 : usable(std::move(usable)) {}

void EventAttachUsable::process(Player& player, Protocol& protocol) {
	printf("Sending Usable id: %d %d\n", usable->get_id(), usable->get_ammo());
	//protocol.sendUsableId(usable->get_id(), usable->get_ammo());
	player.get_usables().emplace(usable->get_id(), std::move(usable));
}
