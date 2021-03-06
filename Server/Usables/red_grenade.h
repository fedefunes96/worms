#ifndef RED_GRENADE_H
#define RED_GRENADE_H

#include "usable.h"
#include "Box2D/Box2D.h"
#include "worm.h"

#define RED_GRENADE_ID 3

class RedGrenade : public Usable {
private:
	const float velocity;
	const float radius;
	const float restitution;
	const float max_dmg;
	const float max_pushback;
	const float radius_expl;

	const int ammount_fragments;
	const float velocity_frag;
	const float radius_frag;
	const float max_dmg_frag;	

public:
	RedGrenade(Stage& stage
	, const int ammo
	, const float velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const float max_pushback
	, const float radius_expl
	, const int ammount_fragments
	, const float velocity_frag
	, const float radius_frag
	, const float max_dmg_frag);

	virtual void action(
		Worm* worm
		, const b2Vec2& dest_pos
		, const std::vector<int> params) override;

	virtual int get_id() override;
};

#endif
