#include "event_actual_player.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"

EventActualPlayer::EventActualPlayer(const int id, const int worm_id)
	: id(id), worm_id(worm_id) {}

void EventActualPlayer::process(Player& player, ProtocolServer& protocol) {
	protocol.sendActualPlayer(id, worm_id);
}
