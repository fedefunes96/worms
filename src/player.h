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
#include "event_queue.h"

class Player : public Thread {
private:
	int id;
	int second_counter;
	bool should_receive;
	bool connected;
	bool in_game;
	bool can_attack;

	int id_actual_worm;

	Counter counter;

	Socket socket;
	Protocol protocol;
	std::unordered_map<int, std::unique_ptr<Usable>> usables;
	//std::unordered_map<int, Worm*> worms;
	std::unordered_map<int, std::shared_ptr<Worm>> worms;

	std::vector<int> worms_ids;

	std::mutex turn_m;
	std::mutex worms_m;

	std::thread event_t;

	EventQueue event_queue;

	void set_receive(bool state);
	void disconnected_player();
	void process_events();

public:
	Player(Socket socket, const int id);
	Player(Player&&);

	void play();
	virtual void run() override;
	void game_loop();
	bool lost();

	//void attach_worm(Worm* worm);
	void attach_worm(std::shared_ptr<Worm> worm);
	void attach_usable(std::unique_ptr<Usable> usable);

	void notify_winner(int id);
	void notify_actual_player(int id);
	void notify_removal(Ubicable* ubicable);
	void notify_position(Ubicable* ubicable, float x, float y, float angle);
	void notify_health(Worm* worm);

	void set_id(int id);
	int get_id();

	bool is_in_game();
	void disconnect();
	void shutdown();
	void stop_events();
	void set_connected(bool state);
	bool should_i_receive();
	void stop_turn();

	bool is_disconnected();

	EventQueue* get_event_queue();

	std::unordered_map<int, std::unique_ptr<Usable>>& get_usables();

	std::unordered_map<int, std::shared_ptr<Worm>>& get_worms();

	std::vector<int>& get_worms_ids();	

	int get_actual_worm();
	void new_worm_id();
};

#endif
