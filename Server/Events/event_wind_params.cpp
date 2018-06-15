#include "event_wind_params.h"
#include "event.h"
#include "protocol.h"
#include "player.h"

EventWindParams::EventWindParams(const float min, const float max)
	: min(min), max(max) {}

void EventWindParams::process(Player& player, Protocol& protocol) {
	printf("Sending Params %0.1f %0.1f\n", min, max);
	protocol.sendWindParams(min, max);
}
