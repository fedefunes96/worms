#ifndef DYNAMITE_H
#define DYNAMITE_H

#include "usable.h"
#include <Box2D/Box2D.h>
#include "worm.h"

#define DYNAMITE_ID 6

class Dynamite : public Usable {
private:
	const float radius;
	const float restitution;
	const float max_dmg;
	const float max_pushback;
	const float radius_expl;

public:
	Dynamite(Stage& stage
	, const int ammo
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
