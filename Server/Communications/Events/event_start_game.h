#ifndef EVENT_START_GAME
#define EVENT_START_GAME

#include "event.h"
#include "protocol_server.h"
#include <string>
#include "player.h"

class EventStartGame : public Event {
private:
	const std::string background;
public:
	EventStartGame(const std::string background);

	virtual void process(Player& player, ProtocolServer& protocol) override;
};

#endif
