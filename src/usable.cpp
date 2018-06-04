#include "usable.h"
#include <Box2D/Box2D.h>

Usable::Usable(Stage& stage, const int ammo) : stage(stage) {
	this->ammo = ammo;
}

void Usable::use(const float longitude
	, const float height		
	, const b2Vec2& from_pos
	, const b2Vec2& dest_pos
	, const std::vector<float>& params) {
	//Check ammo
	if (this->ammo > 0) {
		this->action(longitude, height, from_pos, dest_pos, params);
		this->ammo--;
	} else if (this->ammo == INFINITY_AMMO) {
		this->action(longitude, height, from_pos, dest_pos, params);
	} else {
		//No ammo
	}
}

int Usable::get_ammo() {
	return this->ammo;
}