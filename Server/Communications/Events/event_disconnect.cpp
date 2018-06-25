#include "event_disconnect.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"

EventDisconnect::EventDisconnect() {}

void EventDisconnect::process(Player& player, ProtocolServer& protocol) {
	protocol.sendDisconnect();
	player.shutdown();
}
