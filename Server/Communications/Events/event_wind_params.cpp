#include "event_wind_params.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"

EventWindParams::EventWindParams(const float min, const float max)
	: min(min), max(max) {}

void EventWindParams::process(Player& player, ProtocolServer& protocol) {
	protocol.sendWindParams(min, max);
}
