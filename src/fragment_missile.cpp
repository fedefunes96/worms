#include "fragment_missile.h"
#include "throwable.h"

FragmentMissile::FragmentMissile(Stage& stage
	, Worm* owner
	, const float x
	, const float y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float radius
	, const float max_dmg
	, const float max_pushback
	, const float radius_expl) 
	: Throwable(stage
		, owner
		, x
		, y
		, angle_rad
		, velocity
		, radius
		, 0.0
		, max_dmg
		, max_pushback
		, radius_expl) {}

std::string FragmentMissile::get_type() {
	return FRAGMENT_TYPE;
}

bool FragmentMissile::is_affected_by_wind() {
	return true;
}