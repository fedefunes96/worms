#ifndef GAME_H
#define GAME_H

#include "player.h"
//#include "stage.h"
#include <vector>
#include "thread.h"
#include <thread>
#include <string>
#include "ubicable.h"
#include "water.h"

#include "girder.h"
#include "worm.h"
#include "throwable.h"
#include "event_queue.h"

class Stage;

enum Game_status {
	UNDEFINED = 0,
	WINNER,
	DRAW
};

class Game : public Thread {
private:
	std::vector<Player*> players;
	std::vector<EventQueue*> event_queues;
	Stage stage;

	int id_player_list;
	bool is_over;

	std::string stage_file;

	std::thread stage_t;

	Player* get_actual_player();
	void end_game(Game_status game_status);
	void notify_winner(); 
	Game_status check_for_winner();
	Game_status round_over();
	
	void initialize_game(const std::string& stage_file);
	void start_game();
	void new_player();

	void notify_actual_player(const int id, const int worm_id);

public:
	Game(const std::string& stage_file
		, std::vector<Player*> players
		, std::vector<EventQueue*> event_queues);
	~Game();

	void notify_health(Worm* worm);
	
	void game_loop();
	virtual void run() override;
	bool game_finished();
	void notify_worm_status(int id, bool ground, MoveDirection facing_direction);
};

#endif
