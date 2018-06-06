#include "baseball_bat.h"
#include "usable.h"
#include <Box2D/Box2D.h>
#include "worm.h"

BaseballBat::BaseballBat(Stage& stage
	, const int ammo
	, const float dmg) 
	: Usable(stage, ammo) 
	, dmg(dmg) {}


void BaseballBat::action(Worm* worm
	, const b2Vec2& dest_pos
	, const std::vector<float>& params) {

	/*b2Body* b = worm->get_body();

	b2Vec2 from_pos = b->GetPosition();

	int time = static_cast<int>(params[1]);*/

	//Query pos and do dmg in Area
}

int BaseballBat::get_id() {
	return BASEBALL_BAT_ID;
}
