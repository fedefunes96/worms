#include "event.h"
#include <string>

Event::Event(const std::string name) : name(name) {}

const std::string& Event::get_name() {
	return this->name;
}
