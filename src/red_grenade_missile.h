#ifndef RED_GRENADE_MISSILE_H
#define RED_GRENADE_MISSILE_H

#include "delayed_throwable.h"

#define RED_GRENADE_TYPE "RedGrenade"

class RedGrenadeMissile : public DelayedThrowable {
private:
	const int ammount_fragments;
	const float velocity_frag;
	const float angular_velocity_frag;
	const float radius_frag;
	const float restitution_frag;
	const float max_dmg_frag;

	void create_fragments();

public:
	RedGrenadeMissile(Stage& stage
	, Worm* owner
	, const int x
	, const int y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const int time
	, const int ammount_fragments
	, const float velocity_frag
	, const float angular_velocity_frag
	, const float radius_frag
	, const float restitution_frag
	, const float max_dmg_frag	
	);

	virtual std::string get_type() override;
	virtual bool is_affected_by_wind() override;
	virtual void explode() override;
};

#endif
