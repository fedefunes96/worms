#ifndef GAME_H
#define GAME_H

#include "player.h"
//#include "stage.h"
#include <vector>
#include "common_thread.h"
#include <thread>
//#include "ubicable.h"
#include "girder.h"
#include "worm.h"
#include "throwable.h"

class Stage;

enum Game_status {
	UNDEFINED = 0,
	WINNER,
	DRAW
};

class Game : public Thread {
private:
	Stage stage;
	std::vector<Player> players;
	int id_actual_player;
	std::thread stage_t;
	//Player winner;
	//std::vector<Player>::iterator it_actual_player;

	Player& get_actual_player();
	void end_game(Game_status game_status);
	void notify_winner(); 
	Game_status check_for_winner();
	Game_status round_over();
	void initialize_game();

	void notify_actual_player(const int id);
public:
	Game(/*Stage stage, */std::vector<Player> players);
	~Game();

	void notify_position(Ubicable* ubicable, float x, float y);
	void notify_removal(Ubicable* ubicable);

	virtual void run() override;
};

#endif
