#include "event_actual_player.h"
#include "event.h"
#include "protocol.h"
#include "player.h"

EventActualPlayer::EventActualPlayer(const int id, const int worm_id)
	: id(id), worm_id(worm_id) {}

void EventActualPlayer::process(Player& player, Protocol& protocol) {
	printf("Actual Player id: %d Worm id: %d\n", id, worm_id);
	protocol.sendActualPlayer(id);
	protocol.sendActualWorm(worm_id);
	//Its my turn, send worm id
	/*if (id == player.get_id()) {
		printf("Sending id worm: \n");
		player.new_worm_id();
		int actual_worm = player.get_actual_worm();

		while (player.get_worms().at(actual_worm)->im_dead()) {
			player.new_worm_id();
			actual_worm = player.get_actual_worm();		
		}

		printf("%d\n", actual_worm);

		protocol.sendActualWorm(actual_worm);
	}*/
}
