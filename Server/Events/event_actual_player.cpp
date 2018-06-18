#include "event_actual_player.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"

EventActualPlayer::EventActualPlayer(const int id, const int worm_id)
	: id(id), worm_id(worm_id) {}

void EventActualPlayer::process(Player& player, ProtocolServer& protocol) {
	printf("Actual Player id: %d Worm id: %d\n", id, worm_id);
	protocol.sendActualPlayer(id);
	protocol.sendActualWorm(worm_id);
}
