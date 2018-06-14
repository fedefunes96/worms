#include "event_wind_speed.h"
#include "event.h"
#include "protocol.h"
#include "player.h"

EventWindSpeed::EventWindSpeed(const float speed)
	: speed(speed) {}

void EventWindSpeed::process(Player& player, Protocol& protocol) {
	printf("Sending Wind %0.1f\n", speed);
	protocol.sendWindSpeed(speed);
}
