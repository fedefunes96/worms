#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include "block_queue.h"
#include "event.h"

class EventQueue {
private:
	BlockQueue<Event> block_queue;

public:
	void add_event(Event event);
	Event get_event();
};


#endif
