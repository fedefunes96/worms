#ifndef EVENT_ATTACH_USABLE_H
#define EVENT_ATTACH_USABLE_H

#include "event.h"
#include "protocol_server.h"
#include <string>
#include "player.h"
#include "usable.h"

class EventAttachUsable : public Event {
private:
	std::unique_ptr<Usable> usable;

public:
	EventAttachUsable(std::unique_ptr<Usable> usable);

	virtual void process(Player& player, ProtocolServer& protocol) override;
};

#endif
