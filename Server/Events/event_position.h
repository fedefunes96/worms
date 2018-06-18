#ifndef EVENT_POSITION_H
#define EVENT_POSITION_H

#include "event.h"
#include "protocol_server.h"
#include <string>
#include "player.h"

class EventPosition : public Event {
private:
	//No reference, object may die as im still waiting
	//to process the event
	const std::string type;
	const int id;
	const float x;
	const float y;
	const float angle;

public:
	EventPosition(const std::string type
		, const int id
		, const float x
		, const float y
		, const float angle);

	virtual void process(Player& player, ProtocolServer& protocol) override;
};

#endif
