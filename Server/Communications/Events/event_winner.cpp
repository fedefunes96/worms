#include "event_winner.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"

EventWinner::EventWinner(const int id)
	: id(id) {}

void EventWinner::process(Player& player, ProtocolServer& protocol) {
	protocol.sendWinner(id);
}
