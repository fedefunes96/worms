#include "red_grenade_missile.h"
#include "fragment_missile.h"
#include "delayed_throwable.h"

RedGrenadeMissile::RedGrenadeMissile(Stage& stage
	, Worm* owner
	, const int x
	, const int y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const int time
	, const int ammount_fragments
	, const float velocity_frag
	, const float angular_velocity_frag
	, const float radius_frag
	, const float restitution_frag
	, const float max_dmg_frag) 
	: DelayedThrowable(stage
		, owner
		, x
		, y
		, angle_rad
		, velocity
		, angular_velocity
		, radius
		, restitution
		, max_dmg
		, time)
	, ammount_fragments(ammount_fragments)
	, velocity_frag(velocity_frag)
	, angular_velocity_frag(angular_velocity_frag)
	, radius_frag(radius_frag)
	, restitution_frag(restitution_frag)
	, max_dmg_frag(max_dmg_frag) {}

std::string RedGrenadeMissile::get_type() {
	return RED_GRENADE_TYPE;
}

bool RedGrenadeMissile::is_affected_by_wind() {
	return false;
}

void RedGrenadeMissile::explode() {
	this->create_fragments();
	DelayedThrowable::explode();
}

void RedGrenadeMissile::create_fragments() {
	//Create fragments between pi/4 and 3pi/4 (45° and 135°)

	float32 dist = ((3/4*b2_pi)-(b2_pi/4));

	for (int i = 1; i <= this->ammount_fragments; i++) {
		float32 angle = dist * i/this->ammount_fragments + b2_pi/4;

		b2Vec2 pos = this->body->GetPosition();

		b2Vec2 velocity_missile(this->velocity_frag * cos(angle), velocity_frag * sin(angle));

		FragmentMissile* missile = new FragmentMissile(this->stage
													, this->owner
													, pos.x
													, pos.y
													, angle
													, velocity_missile
													, this->angular_velocity_frag
													, this->radius_frag
													, this->restitution_frag
													, this->max_dmg_frag);

		this->stage.insert(std::move(std::shared_ptr<Movable>(missile)));
	}
}
