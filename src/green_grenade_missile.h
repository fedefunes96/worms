#ifndef GREEN_GRENADE_MISSILE_H
#define GREEN_GRENADE_MISSILE_H

#include "delayed_throwable.h"

#define GREEN_GRENADE_TYPE "GreenGrenade"

class GreenGrenadeMissile : public DelayedThrowable {
public:
	GreenGrenadeMissile(Stage& 
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
