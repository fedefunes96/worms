#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
private:
	const std::string name;
public:
	Event(const std::string name);
	const std::string& get_name();
};

#endif
