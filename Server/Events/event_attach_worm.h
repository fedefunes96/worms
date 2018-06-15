#ifndef EVENT_ATTACH_WORM_H
#define EVENT_ATTACH_WORM_H

#include "event.h"
#include "protocol.h"
#include <string>
#include "player.h"
#include "worm.h"

class EventAttachWorm : public Event {
private:
	const int id;
	std::shared_ptr<Worm> worm;

public:
	EventAttachWorm(const int id, std::shared_ptr<Worm> worm);

	virtual void process(Player& player, Protocol& protocol) override;
};

#endif
