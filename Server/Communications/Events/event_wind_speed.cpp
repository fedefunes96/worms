#include "event_wind_speed.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"

EventWindSpeed::EventWindSpeed(const float speed)
	: speed(speed) {}

void EventWindSpeed::process(Player& player, ProtocolServer& protocol) {
	protocol.sendWindSpeed(speed);
}
