#include "event_disconnect.h"
#include "event.h"
#include "protocol.h"
#include "player.h"

EventDisconnect::EventDisconnect() {}

void EventDisconnect::process(Player& player, Protocol& protocol) {
	printf("Sending disconnect\n");
	protocol.sendDisconnect();
	player.shutdown();
}
