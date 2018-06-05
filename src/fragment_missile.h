#ifndef FRAGMENT_MISSILE_H
#define FRAGMENT_MISSILE_H

#include "throwable.h"

#define FRAGMENT_TYPE "Fragment"

class FragmentMissile : public Throwable {
public:
	FragmentMissile(Stage& stage
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
