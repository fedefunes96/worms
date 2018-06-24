#ifndef EVENT_SHOW_MAPS_GAME
#define EVENT_SHOW_MAPS_GAME

#include "event.h"
#include "protocol_server.h"
#include <string>
#include "player.h"

class EventShowMaps : public Event {
private:
	const std::vector<std::string> maps;
public:
	EventShowMaps(const std::vector<std::string> maps);

	virtual void process(Player& player, ProtocolServer& protocol) override;
};

#endif
