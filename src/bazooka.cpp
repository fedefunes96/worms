#include "bazooka.h"
#include "usable.h"
#include <Box2D/Box2D.h>
#include "bazooka_missile.h"

Bazooka::Bazooka(Stage& stage, int ammo) : Usable(stage, ammo) {}

void Bazooka::action(const b2Vec2& from_pos, const b2Vec2& dest_pos, std::vector<float> params) {
	//Throwable!
	
	//NormalMissile missile(from_pos, restitution, max_dmg, radius);

	/*float32 angle = atan2(dest_pos.y - from_pos.y, dest_pos.x - from_pos.x);

	b2Vec2 where(from_pos.x * cos(angle), from_pos.y * sin(angle));

	BazookaMissile(this->stage
		, where.x
		, where.y
		, angle
		, b2Vec2(10, 10)
		, 2.0
		, 20.0
		, 0.2
		, 50.0);*/
}

int Bazooka::get_id() {
	return BAZOOKA_ID;
}