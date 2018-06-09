#ifndef BAZOOKA_MISSILE_H
#define BAZOOKA_MISSILE_H

#include "throwable.h"

#define BAZOOKA_TYPE "Bazooka"

class BazookaMissile : public Throwable {
public:
	BazookaMissile(Stage& stage
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
