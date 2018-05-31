#include "bazooka.h"
#include "usable.h"
#include <Box2D/Box2D.h>

Bazooka::Bazooka(int ammo) : Usable(ammo) {}

void Bazooka::action(const b2Vec2& from_pos, const b2Vec2& dest_pos, std::vector<float> params) {
	//Throwable!
	
	//NormalMissile missile(from_pos, restitution, max_dmg, radius);
}

int Bazooka::get_id() {
	return BAZOOKA_ID;
}