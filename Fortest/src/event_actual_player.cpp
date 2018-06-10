#include "event_actual_player.h"
#include "event.h"
#include "protocol.h"
#include "player.h"

EventActualPlayer::EventActualPlayer(const int id)
	: id(id) {}

void EventActualPlayer::process(Player& player, Protocol& protocol) {
	printf("Actual Player id: %d\n", id);
	//protocol.sendActualPlayer(id);

	//Its my turn, send worm id
	if (id == player.get_id()) {
		player.new_worm_id();
		int actual_worm = player.get_actual_worm();

		while (player.get_worms().at(actual_worm)->im_dead()) {
			player.new_worm_id();
			actual_worm = player.get_actual_worm();		
		}

		//protocol.sendActualWorm(actual_worm);
	}
}
