#ifndef EVENT_H
#define EVENT_H

class Protocol;
class Player;

class Event {
public:
	virtual void process(Player& player, Protocol& protocol) = 0;
};

#endif
