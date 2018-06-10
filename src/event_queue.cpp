#include "event_queue.h"
#include "block_queue.h"
#include "event.h"
#include <string>

EventQueue::EventQueue() {}

void EventQueue::add_event(std::shared_ptr<Event> event) {
	this->block_queue.push(std::move(event));
}

std::shared_ptr<Event> EventQueue::get_event() {
	return std::move(this->block_queue.pop());
}

EventQueue::EventQueue(EventQueue&& other)
 : block_queue(std::move(other.block_queue)) {}