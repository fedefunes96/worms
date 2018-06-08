#ifndef BANANA_H
#define BANANA_H

#include "usable.h"
#include <Box2D/Box2D.h>
#include "worm.h"

#define BANANA_ID 4

class Banana : public Usable {
private:
	const float velocity;
	const float angular_velocity;
	const float radius;
	const float restitution;
	const float max_dmg;

public:
	Banana(Stage& stage
	, const int ammo
	, const float velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg);

	/*virtual void action(
		const float longitude
		, const float height
		, const b2Vec2& from_pos
		, const b2Vec2& dest_pos
		, const std::vector<float>& params) override;*/
	virtual void action(
		Worm* worm
		, const b2Vec2& dest_pos
		, const std::vector<int>& params) override;

	virtual int get_id() override;
};

#endif
