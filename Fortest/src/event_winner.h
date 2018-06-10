#ifndef EVENT_WINNER_H
#define EVENT_WINNER_H

#include "event.h"
#include "protocol.h"
#include <string>
#include "player.h"

class EventWinner : public Event {
private:
	const int id;

public:
	EventWinner(const int id);

	virtual void process(Player& player, Protocol& protocol) override;
};

#endif
