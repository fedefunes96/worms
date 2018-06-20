#ifndef EVENT_WIND_PARAMS_H
#define EVENT_WIND_PARAMS_H

#include "event.h"
#include "protocol_server.h"
#include <string>
#include "player.h"

class EventWindParams : public Event {
private:
	const float min;
	const float max;

public:
	EventWindParams(const float min, const float max);

	virtual void process(Player& player, ProtocolServer& protocol) override;
};

#endif
