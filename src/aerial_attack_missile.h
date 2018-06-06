#ifndef AERIAL_ATTACK_MISSILE_H
#define AERIAL_ATTACK_MISSILE_H

#include "throwable.h"

#define AERIAL_ATTACK_TYPE "AerialAttack"

class AerialAttackMissile : public Throwable {
public:
	AerialAttackMissile(Stage& stage
	, Worm* owner
	, const int x
	, const int y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg);

	virtual std::string get_type() override;
	virtual bool is_affected_by_wind() override;
};

#endif
