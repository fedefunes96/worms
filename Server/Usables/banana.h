#ifndef BANANA_H
#define BANANA_H

#include "usable.h"
#include "Box2D/Box2D.h"
#include "worm.h"

#define BANANA_ID 4

class Banana : public Usable {
private:
	const float velocity;
	const float radius;
	const float restitution;
	const float max_dmg;
	const float max_pushback;
	const float radius_expl;

public:
	Banana(Stage& stage
	, const int ammo
	, const float velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const float max_pushback
	, const float radius_expl);

	virtual void action(
		Worm* worm
		, const b2Vec2& dest_pos
		, const std::vector<int> params) override;

	virtual int get_id() override;
};

#endif
