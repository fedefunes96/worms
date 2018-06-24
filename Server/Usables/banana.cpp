#include "banana.h"
#include "usable.h"
#include "Box2D/Box2D.h"
#include "banana_missile.h"
#include "worm.h"

Banana::Banana(Stage& stage
	, const int ammo
	, const float velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const float max_pushback
	, const float radius_expl) 
	: Usable(stage, ammo) 
	, velocity(velocity)
	, radius(radius)
	, restitution(restitution)
	, max_dmg(max_dmg)
	, max_pushback(max_pushback)
	, radius_expl(radius_expl) {}

void Banana::action(Worm* worm
	, const b2Vec2& dest_pos
	, const std::vector<int> params) {

	printf("Using Banana\n");

	b2Body* b = worm->get_body();

	b2Vec2 from_pos = b->GetPosition();

	b2Vec2 normalized_dest = dest_pos - from_pos;

	float32 angle = atan2(normalized_dest.y, normalized_dest.x);

	float velocity_f = this->velocity * TRANSF_POT_VAR(float(params[0]))/100.0;

	b2Vec2 vec_velocity(velocity_f * cos(angle), velocity_f * sin(angle));

	int time = params[1];

	BananaMissile* missile = new BananaMissile(this->stage
												, worm
												, from_pos.x
												, from_pos.y
												, angle
												, vec_velocity
												, this->radius
												, this->restitution
												, this->max_dmg
												, this->max_pushback
												, this->radius_expl
												, time);

	this->stage.insert(std::move(std::shared_ptr<Movable>(missile)));
}

int Banana::get_id() {
	return BANANA_ID;
}
