#ifndef BAZOOKA_MISSILE_H
#define BAZOOKA_MISSILE_H

#include "throwable.h"

#define BAZOOKA_TYPE "Bazooka"

class BazookaMissile : public Throwable {
public:
	BazookaMissile(Stage& stage
	, const int x
	, const int y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg);

	virtual std::string get_type() override;
};

#endif
