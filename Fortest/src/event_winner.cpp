#include "event_winner.h"
#include "event.h"
#include "protocol.h"
#include "player.h"

EventWinner::EventWinner(const int id)
	: id(id) {}

void EventWinner::process(Player& player, Protocol& protocol) {
	printf("Sending Winner\n");
	//protocol.sendWinner(id);
}
