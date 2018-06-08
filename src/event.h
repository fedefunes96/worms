#ifndef EVENT_H
#define EVENT_H

#include <string>
#include "protocol.h"

class Event {
public:
	virtual void process(Protocol& protocol) = 0;
	virtual void execute() = 0;
};

#endif
