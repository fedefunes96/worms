#ifndef EVENT_REMOVE_H
#define EVENT_REMOVE_H

#include "event.h"
#include "protocol.h"
#include <string>
#include "player.h"

class EventRemove : public Event {
private:
	const std::string type;
	const int id;

public:
	EventRemove(const std::string type, const int id);

	virtual void process(Player& player, Protocol& protocol) override;
};

#endif
