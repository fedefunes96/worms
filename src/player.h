#ifndef PLAYER_H
#define PLAYER_H

#include "usable.h"
#include "worm.h"
#include "thread.h"
#include <unordered_map>
#include <memory>
#include "protocol.h"
#include "ubicable.h"
#include "counter.h"

class Player {
private:
	int id;
	int second_counter;
	bool my_turn;
	bool continue_receiving;
	Counter counter;

	Protocol protocol;
	std::unordered_map<int, std::unique_ptr<Usable>> usables;
	//std::unordered_map<int, Worm*> worms;
	std::unordered_map<int, std::shared_ptr<Worm>> worms;

	std::mutex turn_m;
	std::mutex worms_m;

	bool is_my_turn();
	void set_turn(bool state);
public:
	Player(Protocol protocol);
	Player(Player&&);

	void play();
	void game_loop();
	bool lost();

	//void attach_worm(Worm* worm);
	void attach_worm(std::shared_ptr<Worm> worm);
	void attach_usable(std::unique_ptr<Usable> usable);

	void notify_winner(int id);
	void notify_game_end();
	void notify_actual_player(int id);
	void notify_removal(Ubicable* ubicable);
	void notify_position(Ubicable* ubicable, float x, float y, float angle);

	void set_id(int id);
	int get_id();
};

#endif
