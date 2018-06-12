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
	std::vector<std::unique_ptr<Ubicable>> ubicables;
	std::vector<EventQueue*> event_queues;
	Stage stage;
	//std::vector<std::unique_ptr<Worm>> worms;
	//std::vector<std::unique_ptr<Girder>> girders;

	//int id_actual_player;
	int id_player_list;
	bool is_over;

	std::string stage_file;

	std::thread stage_t;
	//std::thread game_t;
	std::vector<std::thread> players_t;
	//Player winner;
	//std::vector<Player>::iterator it_actual_player;

	Player* get_actual_player();
	void end_game(Game_status game_status);
	void notify_winner(); 
	Game_status check_for_winner();
	Game_status round_over();
	
	void initialize_players();
	void initialize_game(const std::string& stage_file);
	void start_game();
	void new_player();

	void notify_actual_player(const int id);


public:
	Game(const std::string& stage_file
		, std::vector<Player*> players
		, std::vector<EventQueue*> event_queues);
	~Game();

	void notify_position(Ubicable* ubicable, float x, float y, float angle);
	void notify_removal(Ubicable* ubicable);
	void notify_health(Worm* worm);
	
	void game_loop();
	virtual void run() override;
	bool game_finished();
	//virtual void run() override;
	void notify_worm_status(int id,bool ground,MoveDirection facing_direction);
};

#endif
