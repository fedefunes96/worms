#ifndef EVENT_DISCONNECT_H
#define EVENT_DISCONNECT_H

#include "event.h"
#include "protocol.h"
#include <string>
#include "player.h"

class EventDisconnect : public Event {

public:
	EventDisconnect();

	virtual void process(Player& player, Protocol& protocol) override;
};

#endif
