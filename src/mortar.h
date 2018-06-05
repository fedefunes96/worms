#ifndef MORTAR_H
#define MORTAR_H

#include "usable.h"
#include <Box2D/Box2D.h>
#include "worm.h"

#define MORTAR_ID 1

class Mortar : public Usable {
private:
	const float velocity;
	const float angular_velocity;
	const float radius;
	const float restitution;
	const float max_dmg;

	const int ammount_fragments;
	const float velocity_frag;
	const float angular_velocity_frag;
	const float radius_frag;
	const float restitution_frag;
	const float max_dmg_frag;	

public:
	Mortar(Stage& stage
	, const int ammo
	, const float velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const int ammount_fragments
	, const float velocity_frag
	, const float angular_velocity_frag
	, const float radius_frag
	, const float restitution_frag
	, const float max_dmg_frag);

	/*virtual void action(
		const float longitude
		, const float height
		, const b2Vec2& from_pos
		, const b2Vec2& dest_pos
		, const std::vector<float>& params) override;*/
	virtual void action(
		Worm* worm
		, const b2Vec2& dest_pos
		, const std::vector<float>& params) override;

	virtual int get_id() override;
};

#endif
