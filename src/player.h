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
	int id;
	int second_counter;
	bool my_turn;
	bool continue_receiving;

	Protocol protocol;
	std::unordered_map<int, std::unique_ptr<Usable>&> usables;
	std::unordered_map<int, Worm&> worms;

	bool is_my_turn();
	void set_turn();
	int get_second_counter();
	void set_second_counter(int count);
public:
	Player(Protocol protocol);
	//Player(Player&&);
	void play();
	void start_receiving();
	bool lost();

	void attach_worm(std::unique_ptr<Worm>& worm);
	void attach_usable(int id, std::unique_ptr<Usable>& usable);

	void notify_actual_player(int id);
	void notify_removal(Ubicable* ubicable);
	void notify_position(Ubicable* ubicable, float x, float y, float angle);

	void set_id(int id);
	int get_id();
};

#endif
