#ifndef GREEN_GRENADE_MISSILE_H
#define GREEN_GRENADE_MISSILE_H

#include "delayed_throwable.h"

#define GREEN_GRENADE_TYPE "GreenGrenade"

class GreenGrenadeMissile : public DelayedThrowable {
public:
	GreenGrenadeMissile(Stage& 
	, Worm* owner
	, const float x
	, const float y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const float max_pushback
	, const float radius_expl
	, const int time);

	virtual std::string get_type() override;
	virtual bool is_affected_by_wind() override;
};

#endif
