#include "usable.h"
#include "Box2D/Box2D.h"
#include "worm.h"

Usable::Usable(Stage& stage, const int ammo) : stage(stage) {
	this->ammo = ammo;
}

void Usable::use(Worm* worm
	, const b2Vec2& dest_pos
	, const std::vector<int> params) {
	//Check ammo
	if (this->ammo > 0) {
		this->action(worm, dest_pos, std::move(params));
		this->ammo--;
	} else if (this->ammo == INFINITY_AMMO) {
		this->action(worm, dest_pos, std::move(params));
	} else {
		//No ammo
	}
}
int Usable::get_ammo() {
	return this->ammo;
}