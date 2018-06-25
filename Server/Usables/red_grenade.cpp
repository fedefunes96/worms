#include "red_grenade.h"
#include "usable.h"
#include "Box2D/Box2D.h"
#include "red_grenade_missile.h"
#include "worm.h"

RedGrenade::RedGrenade(Stage& stage
	, const int ammo
	, const float velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const float max_pushback
	, const float radius_expl
	, const int ammount_fragments
	, const float velocity_frag
	, const float radius_frag
	, const float max_dmg_frag) 
	: Usable(stage, ammo) 
	, velocity(velocity)
	, radius(radius)
	, restitution(restitution)
	, max_dmg(max_dmg)
	, max_pushback(max_pushback)
	, radius_expl(radius_expl)	
	, ammount_fragments(ammount_fragments)
	, velocity_frag(velocity_frag)
	, radius_frag(radius_frag)
	, max_dmg_frag(max_dmg_frag) {}

void RedGrenade::action(Worm* worm
	, const b2Vec2& dest_pos
	, const std::vector<int> params) {

	b2Body* b = worm->get_body();

	b2Vec2 from_pos = b->GetPosition();

	b2Vec2 normalized_dest = dest_pos - from_pos;

	float32 angle = atan2(normalized_dest.y, normalized_dest.x);

	float velocity_f = this->velocity * TRANSF_POT_VAR(float(params[0]))/100.0;

	b2Vec2 vec_velocity(velocity_f * cos(angle), velocity_f * sin(angle));

	int time = params[1];


	RedGrenadeMissile* missile = new RedGrenadeMissile(this->stage
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
												, time
												, this->ammount_fragments
												, this->velocity_frag
												, this->radius_frag
												, this->max_dmg_frag);

	this->stage.insert(std::move(std::shared_ptr<Movable>(missile)));
}

int RedGrenade::get_id() {
	return RED_GRENADE_ID;
}