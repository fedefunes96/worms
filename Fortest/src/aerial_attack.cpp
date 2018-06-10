#include "aerial_attack.h"
#include "usable.h"
#include <Box2D/Box2D.h>
#include "aerial_attack_missile.h"
#include "worm.h"

AerialAttack::AerialAttack(Stage& stage
	, const int ammo
	, const float velocity
	, const float radius
	, const float max_dmg
	, const float from_create_y
	, const float max_pushback
	, const float radius_expl) 
	: Usable(stage, ammo) 
	, velocity(velocity)
	, radius(radius)
	, max_dmg(max_dmg)
	, from_create_y(from_create_y)
	, max_pushback(max_pushback)
	, radius_expl(radius_expl) {}

void AerialAttack::action(Worm* worm
	, const b2Vec2& dest_pos
	, const std::vector<int> params) {

	printf("Using AerialAttack\n");

	//6 radius between each missile (6 missile separation)
	float separation = 6 * radius;

	for (int i = 0; i < AMMOUNT; i++) {
		b2Vec2 where(dest_pos.x+separation*(i-2), from_create_y);

		float32 angle = atan2(dest_pos.y - where.y, dest_pos.x - where.x);

		//Only X axis, let the gravity do the rest
		b2Vec2 vec_velocity(this->velocity*cos(angle), 0.0);

		AerialAttackMissile* missile = new AerialAttackMissile(this->stage
														, worm
														, where.x
														, where.y
														, angle
														, vec_velocity
														, this->radius
														, this->max_dmg
														, this->max_pushback
														, this->radius_expl); 	

		this->stage.insert(std::move(std::shared_ptr<Movable>(missile)));											
	}
}

int AerialAttack::get_id() {
	return AERIAL_ATTACK_ID;
}
