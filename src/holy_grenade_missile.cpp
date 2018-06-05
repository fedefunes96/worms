#include "holy_grenade_missile.h"
#include "delayed_throwable.h"

HolyGrenadeMissile::HolyGrenadeMissile(Stage& stage
	, Worm* owner
	, const int x
	, const int y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const int time) 
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
		, time) {}

std::string HolyGrenadeMissile::get_type() {
	return HOLY_GRENADE_TYPE;
}

bool HolyGrenadeMissile::is_affected_by_wind() {
	return false;
}
