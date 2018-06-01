#include "bazooka_missile.h"
#include "throwable.h"

BazookaMissile::BazookaMissile(Stage& stage
	, const int x
	, const int y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg) 
	: Throwable(stage
		, x
		, y
		, angle_rad
		, velocity
		, angular_velocity
		, radius
		, restitution
		, max_dmg) {}

std::string BazookaMissile::get_type() {
	return BAZOOKA_TYPE;
}