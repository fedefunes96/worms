#ifndef BANANA_MISSILE_H
#define BANANA_MISSILE_H

#include "delayed_throwable.h"

#define BANANA_TYPE "Banana"

class BananaMissile : public DelayedThrowable {
public:
	BananaMissile(Stage& stage
	, Worm* owner
	, const int x
	, const int y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const int time);

	virtual std::string get_type() override;
	virtual bool is_affected_by_wind() override;
};

#endif
