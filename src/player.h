#ifndef PLAYER_H
#define PLAYER_H

#include "usable.h"
#include "worm.h"
#include <unordered_map>
#include <memory>
#include "protocolo.h"

class Player {
private:
	Protocolo protocolo;
	std::unordered_map<int, std::unique_ptr<Usable>&> usables;
	std::unordered_map<int, Worm> worms;
public:
	Player(Protocolo protocolo
		, std::unordered_map<int, std::unique_ptr<Usable>&> usables
		, std::unordered_map<int, Worm> worms);
	//Player(Player&&);
	void play();
	bool lost();
};

#endif
