#ifndef EVENT_H
#define EVENT_H

class ProtocolServer;
class Player;

class Event {
public:
	virtual void process(Player& player, ProtocolServer& protocol) = 0;
};

#endif
