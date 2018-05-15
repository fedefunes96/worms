#include "usable.h"
#include <Box2D/Box2D.h>

Usable::Usable(const int ammo) {
	this->ammo = ammo;
}

void Usable::use(const b2Vec2& from_pos, const b2Vec2& dest_pos) {
	//Check ammo
	if (this->ammo > 0) {
		this->action(from_pos, dest_pos);
		this->ammo--;
	} else if (this->ammo == INFINITY_AMMO) {
		this->action(from_pos, dest_pos);
	} else {
		//No ammo
	}
}