#ifndef EVENT_WIND_SPEED_H
#define EVENT_WIND_SPEED_H

#include "event.h"
#include "protocol_server.h"
#include <string>
#include "player.h"

class EventWindSpeed : public Event {
private:
	const float speed;

public:
	EventWindSpeed(const float speed);

	virtual void process(Player& player, ProtocolServer& protocol) override;
};

#endif
