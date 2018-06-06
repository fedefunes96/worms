#include "aerial_attack_missile.h"
#include "throwable.h"

AerialAttackMissile::AerialAttackMissile(Stage& stage
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

std::string AerialAttackMissile::get_type() {
	return AERIAL_ATTACK_TYPE;
}

bool AerialAttackMissile::is_affected_by_wind() {
	return true;
}
