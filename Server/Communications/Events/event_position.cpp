#include "event_position.h"
#include "event.h"
#include "protocol_server.h"
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

void EventPosition::process(Player& player, ProtocolServer& protocol) {
	protocol.sendPosition(type, id, x, y, angle);
}
