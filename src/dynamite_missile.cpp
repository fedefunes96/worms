#include "dynamite_missile.h"
#include "delayed_throwable.h"

DynamiteMissile::DynamiteMissile(Stage& stage
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

std::string DynamiteMissile::get_type() {
	return DYNAMITE_TYPE;
}

bool DynamiteMissile::is_affected_by_wind() {
	return false;
}
