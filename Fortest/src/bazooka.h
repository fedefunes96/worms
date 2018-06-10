#ifndef BAZOOKA_H
#define BAZOOKA_H

#include "usable.h"
#include <Box2D/Box2D.h>
#include "worm.h"

#define BAZOOKA_ID 0

class Bazooka : public Usable {
private:
	const float velocity;
	const float radius;
	const float max_dmg;
	const float max_pushback;
	const float radius_expl;

public:
	Bazooka(Stage& stage
	, const int ammo
	, const float velocity
	, const float radius
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
