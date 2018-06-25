#include "event_show_maps.h"
#include "event.h"
#include "protocol_server.h"
#include "player.h"

EventShowMaps::EventShowMaps(const std::vector<std::string> maps) 
 : maps(std::move(maps)) {}

void EventShowMaps::process(Player& player, ProtocolServer& protocol) {
	protocol.sendMaps(maps);
}
