#ifndef AERIAL_ATTACK_H
#define AERIAL_ATTACK_H

#include "usable.h"
#include <Box2D/Box2D.h>
#include "worm.h"

#define AERIAL_ATTACK_ID 8

class AerialAttack : public Usable {
private:
	const float velocity;
	const float radius;
	const float max_dmg;
	const float highest_obj;
	const float max_pushback;
	const float radius_expl;

public:
	AerialAttack(Stage& stage
	, const int ammo
	, const float velocity
	, const float radius
	, const float max_dmg
	, const float highest_obj
	, const float max_pushback
	, const float radius_expl);

	virtual void action(
		Worm* worm
		, const b2Vec2& dest_pos
		, const std::vector<int>& params) override;

	virtual int get_id() override;
};

#endif
