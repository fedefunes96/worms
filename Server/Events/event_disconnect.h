#ifndef EVENT_DISCONNECT_H
#define EVENT_DISCONNECT_H

#include "event.h"
#include "protocol_server.h"
#include <string>
#include "player.h"

class EventDisconnect : public Event {

public:
	EventDisconnect();

	virtual void process(Player& player, ProtocolServer& protocol) override;
};

#endif
