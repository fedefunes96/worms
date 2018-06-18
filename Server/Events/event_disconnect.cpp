#include "event_disconnect.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"

EventDisconnect::EventDisconnect() {}

void EventDisconnect::process(Player& player, ProtocolServer& protocol) {
	printf("Sending disconnect\n");
	protocol.sendDisconnect();
	player.shutdown();
}
