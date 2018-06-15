#include "event_position.h"
#include "event.h"
#include "protocol.h"
#include "player.h"

EventPosition::EventPosition(const std::string type
	, const int id
	, const float x
	, const float y
	, const float angle)
	: type(type)
	, id(id)
	, x(x)
	, y(y)
	, angle(angle) {}

void EventPosition::process(Player& player, Protocol& protocol) {
	//printf("Sending position: %0.1f %0.1f\n", x, y);

	protocol.sendPosition(type, id, x, y, angle);
}
