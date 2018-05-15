#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "stage.h"
#include <vector>
#include "common_thread.h"

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
	//Player winner;
	//std::vector<Player>::iterator it_actual_player;

	Player& get_actual_player();
	void end_game(Game_status game_status);
	void notify_winner(); 
	Game_status check_for_winner();
	void round_over();
public:
	Game(Stage stage, std::vector<Player> players);

	virtual void run() override;
};

#endif
