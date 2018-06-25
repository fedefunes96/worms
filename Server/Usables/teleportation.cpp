#include "teleportation.h"
#include "usable.h"
#include "Box2D/Box2D.h"
#include "worm.h"

Teleportation::Teleportation(Stage& stage
	, const int ammo) 
	: Usable(stage, ammo) {}

void Teleportation::action(Worm* worm
	, const b2Vec2& dest_pos
	, const std::vector<int> params) {


	//this->stage.set_position(worm, dest_pos);
	worm->set_position(dest_pos);
}

int Teleportation::get_id() {
	return TELEPORTATION_ID;
}
