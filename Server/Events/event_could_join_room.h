#ifndef EVENT_COULD_JOIN_ROOM
#define EVENT_COULD_JOIN_ROOM

#include "event.h"
#include "protocol_server.h"
#include <string>
#include "player.h"

class EventCouldJoinRoom : public Event {
private:
	const bool could;

public:
	EventCouldJoinRoom(const bool could);

	virtual void process(Player& player, ProtocolServer& protocol) override;
};

#endif
