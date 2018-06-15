#ifndef EVENT_ACTUAL_PLAYER_H
#define EVENT_ACTUAL_PLAYER_H

#include "event.h"
#include "protocol.h"
#include <string>
#include "player.h"

class EventActualPlayer : public Event {
private:
	const int id;
	const int worm_id;

public:
	EventActualPlayer(const int id, const int worm_id);

	virtual void process(Player& player, Protocol& protocol) override;
};

#endif
