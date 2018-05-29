#include "event_queue.h"
#include "block_queue.h"
#include "event.h"
#include <string>

void EventQueue::add_event(Event event) {
	this->block_queue.push(event);
}

Event EventQueue::get_event() {
	return this->block_queue.pop();
}
