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

class Server;

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

	Server& server;
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

	void disconnected_player();
	void process_events();

public:
	Player(Server& server, Socket socket, const int id);
	Player(Player&&);

	void play();
	virtual void run() override;
	void game_loop();
	bool lost();

	void attach_worm(std::shared_ptr<Worm> worm);
	void attach_usable(std::unique_ptr<Usable> usable);

	int get_id();

	bool is_in_game();
	void set_in_game(bool state);
	void shutdown();
	void stop_events();
	void set_connected(bool state);
	void set_receive(bool state);
	bool should_i_receive();
	void stop_turn();

	bool is_disconnected();

	EventQueue* get_event_queue();

	int get_actual_worm_id();
	int get_actual_worm();
	void new_worm_id();
};

#endif
