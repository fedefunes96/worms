#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include "block_queue.h"
#include "event.h"

class EventQueue {
private:
	BlockQueue<std::shared_ptr<Event>> block_queue;

public:
	EventQueue();
	void add_event(std::shared_ptr<Event> event);
	std::shared_ptr<Event> get_event();
	EventQueue(EventQueue&& other);
};


#endif
