#ifndef EVENT_SHOW_ROOMS_GAME
#define EVENT_SHOW_ROOMS_GAME

#include "event.h"
#include "protocol_server.h"
#include <string>
#include "player.h"

class EventShowRooms : public Event {
private:
	const std::vector<std::string> rooms;
public:
	EventShowRooms(const std::vector<std::string> rooms);

	virtual void process(Player& player, ProtocolServer& protocol) override;
};

#endif
