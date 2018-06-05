#include "fragment_missile.h"
#include "throwable.h"

FragmentMissile::FragmentMissile(Stage& stage
	, Worm* owner
	, const int x
	, const int y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg) 
	: Throwable(stage
		, owner
		, x
		, y
		, angle_rad
		, velocity
		, angular_velocity
		, radius
		, restitution
		, max_dmg) {}

std::string FragmentMissile::get_type() {
	return FRAGMENT_TYPE;
}

bool FragmentMissile::is_affected_by_wind() {
	return true;
}