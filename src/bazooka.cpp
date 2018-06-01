#include "bazooka.h"
#include "usable.h"
#include <Box2D/Box2D.h>
#include "bazooka_missile.h"

Bazooka::Bazooka(Stage& stage, int ammo) : Usable(stage, ammo) {}

void Bazooka::action(const b2Vec2& from_pos, const b2Vec2& dest_pos, std::vector<float> params) {
	//Throwable!
	
	//NormalMissile missile(from_pos, restitution, max_dmg, radius);

	float32 dot = from_pos.x*dest_pos.x + from_pos.y*dest_pos.y;
	float32 det = from_pos.x*dest_pos.y - from_pos.y*dest_pos.x;

	float32 angle = atan2(det, dot);

	b2Vec2 where(from_pos.x + 2*cos(angle), from_pos.y + 2*sin(angle));

	/*printf("Angle %0.1f Cos %0.1f Sen %0.1f\n", angle, cos(angle), sin(angle));
	printf("From %0.1f %0.1f\n", from_pos.x, from_pos.y);
	printf("Dest %0.1f %0.1f\n", dest_pos.x, dest_pos.y);
	printf("Where %0.1f %0.1f\n", where.x, where.y);*/

	BazookaMissile* missile = new BazookaMissile(this->stage
												, where.x
												, where.y+10
												, angle
												, b2Vec2(0, 100)
												, 0.0
												, 1.0
												, 0
												, 50.0);

	this->stage.insert(std::move(std::shared_ptr<Movable>(missile)));
}

int Bazooka::get_id() {
	return BAZOOKA_ID;
}