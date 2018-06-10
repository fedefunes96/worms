#include "dynamite.h"
#include "usable.h"
#include <Box2D/Box2D.h>
#include "dynamite_missile.h"
#include "worm.h"

Dynamite::Dynamite(Stage& stage
	, const int ammo
	, const float radius
	, const float restitution
	, const float max_dmg
	, const float max_pushback
	, const float radius_expl) 
	: Usable(stage, ammo) 
	, radius(radius)
	, restitution(restitution)
	, max_dmg(max_dmg)
	, max_pushback(max_pushback)
	, radius_expl(radius_expl) {}

void Dynamite::action(Worm* worm
	, const b2Vec2& dest_pos
	, const std::vector<int> params) {

	printf("Using Dynamite\n");

	b2Body* b = worm->get_body();

	b2Vec2 from_pos = b->GetPosition();

	int time = params[0];

	DynamiteMissile* missile = new DynamiteMissile(this->stage
												, worm
												, from_pos.x
												, from_pos.y
												, 0.0
												, b2Vec2(0, 0)
												, this->radius
												, this->restitution
												, this->max_dmg
												, this->max_pushback
												, this->radius_expl
												, time);

	this->stage.insert(std::move(std::shared_ptr<Movable>(missile)));
}

int Dynamite::get_id() {
	return DYNAMITE_ID;
}
