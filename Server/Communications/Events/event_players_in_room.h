#ifndef EVENT_PLAYERS_IN_ROOM
#define EVENT_PLAYERS_IN_ROOM

#include "event.h"
#include "protocol_server.h"
#include <string>
#include "player.h"

class EventPlayersInRoom : public Event {
private:
	const int size;

public:
	EventPlayersInRoom(const int size);

	virtual void process(Player& player, ProtocolServer& protocol) override;
};

#endif
