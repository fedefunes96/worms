#ifndef FRAGMENT_MISSILE_H
#define FRAGMENT_MISSILE_H

#include "throwable.h"

#define FRAGMENT_TYPE "Fragment"

class FragmentMissile : public Throwable {
public:
	FragmentMissile(Stage& stage
	, Worm* owner
	, const float x
	, const float y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float radius
	, const float max_dmg
	, const float max_pushback
	, const float radius_expl);

	virtual std::string get_type() override;
	virtual bool is_affected_by_wind() override;
};

#endif
