#include "red_grenade.h"
#include "usable.h"
#include <Box2D/Box2D.h>
#include "red_grenade_missile.h"
#include "worm.h"

RedGrenade::RedGrenade(Stage& stage
	, const int ammo
	, const float velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const int ammount_fragments
	, const float velocity_frag
	, const float angular_velocity_frag
	, const float radius_frag
	, const float restitution_frag
	, const float max_dmg_frag) 
	: Usable(stage, ammo) 
	, velocity(velocity)
	, angular_velocity(angular_velocity)
	, radius(radius)
	, restitution(restitution)
	, max_dmg(max_dmg)
	, ammount_fragments(ammount_fragments)
	, velocity_frag(velocity_frag)
	, angular_velocity_frag(angular_velocity_frag)
	, radius_frag(radius_frag)
	, restitution_frag(restitution_frag)
	, max_dmg_frag(max_dmg_frag) {}


/*void RedGrenade::action(const float longitude
	, const float height
	, const b2Vec2& from_pos
	, const b2Vec2& dest_pos
	, const std::vector<float>& params) {

	b2Vec2 normalized_dest = dest_pos - from_pos;

	float32 angle = atan2(normalized_dest.y, normalized_dest.x);

	b2Vec2 where(from_pos.x + 2*longitude*cos(angle), from_pos.y + 2*height*sin(angle));
	b2Vec2 vec_velocity(this->velocity * cos(angle), this->velocity * sin(angle));

	int time = static_cast<int>(params[1]);

	RedGrenadeMissile* missile = new RedGrenadeMissile(this->stage
												, where.x
												, where.y
												, angle
												, vec_velocity
												, this->angular_velocity
												, this->radius
												, this->restitution
												, this->max_dmg
												, time
												, this->ammount_fragments
												, this->velocity_frag
												, this->angular_velocity_frag
												, this->radius_frag
												, this->restitution_frag
												, this->max_dmg_frag);

	this->stage.insert(std::move(std::shared_ptr<Movable>(missile)));
}*/
void RedGrenade::action(Worm* worm
	, const b2Vec2& dest_pos
	, const std::vector<int>& params) {

	b2Body* b = worm->get_body();

	b2Vec2 from_pos = b->GetPosition();

	b2Vec2 normalized_dest = dest_pos - from_pos;

	float32 angle = atan2(normalized_dest.y, normalized_dest.x);

	float velocity_f = this->velocity * (float(params[0])/100.0);

	b2Vec2 vec_velocity(velocity_f * cos(angle), velocity_f * sin(angle));

	int time = params[1];

	RedGrenadeMissile* missile = new RedGrenadeMissile(this->stage
												, worm
												, from_pos.x
												, from_pos.y
												, angle
												, vec_velocity
												, this->angular_velocity
												, this->radius
												, this->restitution
												, this->max_dmg
												, time
												, this->ammount_fragments
												, this->velocity_frag
												, this->angular_velocity_frag
												, this->radius_frag
												, this->restitution_frag
												, this->max_dmg_frag);

	this->stage.insert(std::move(std::shared_ptr<Movable>(missile)));
}

int RedGrenade::get_id() {
	return RED_GRENADE_ID;
}