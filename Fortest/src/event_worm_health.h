#ifndef EVENT_WORM_HEALTH_H
#define EVENT_WORM_HEALTH_H

#include "event.h"
#include "protocol.h"
#include <string>
#include "player.h"

class EventWormHealth : public Event {
private:
	const int id;
	const int health;

public:
	EventWormHealth(const int id, const int health);

	virtual void process(Player& player, Protocol& protocol) override;
};

#endif
