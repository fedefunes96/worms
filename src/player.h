#ifndef PLAYER_H
#define PLAYER_H

#include "usable.h"
#include "worm.h"
#include <unordered_map>
#include <memory>
#include "protocol.h"
#include "ubicable.h"

class Player {
private:
	const int id;
	Protocol protocol;
	std::unordered_map<int, std::unique_ptr<Usable>&> usables;
	std::unordered_map<int, Worm> worms;

	void wait_to_play(int time, bool* end);
public:
	Player(const int id
		, Protocol protocol
		, std::unordered_map<int, std::unique_ptr<Usable>&> usables
		, std::unordered_map<int, Worm> worms);
	//Player(Player&&);
	void play();
	bool lost();

	void notify_actual_player(int id);
	void notify_removal(Ubicable* ubicable);
	void notify_position(Ubicable* ubicable, float x, float y);
};

#endif
