#ifndef EVENT_WORM_STATUS_H
#define EVENT_WORM_STATUS_H

#include "event.h"
#include "protocol.h"
#include <string>
#include "player.h"

class EventWormStatus : public Event {
private:
	const int id;
	bool ground;
	MoveDirection dir;

public:
	EventWormStatus(const int id, bool ground, MoveDirection dir);

	virtual void process(Player& player, Protocol& protocol) override;
};

#endif
