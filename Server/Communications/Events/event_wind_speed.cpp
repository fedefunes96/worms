#include "event_wind_speed.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"

EventWindSpeed::EventWindSpeed(const float speed)
	: speed(speed) {}

void EventWindSpeed::process(Player& player, ProtocolServer& protocol) {
	printf("Sending Wind %0.1f\n", speed);
	protocol.sendWindSpeed(speed);
}
