#ifndef EVENT_START_GAME
#define EVENT_START_GAME

#include "event.h"
#include "protocol.h"
#include <string>
#include "player.h"

class EventStartGame : public Event {
public:
	EventStartGame();

	virtual void process(Player& player, Protocol& protocol) override;
};

#endif
