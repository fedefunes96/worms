#ifndef WORM_H
#define WORM_H

#include <vector>
#include <utility>
#include "usable.h"
#include "movable.h"
#include <Box2D/Box2D.h>

class Worm : public Movable {
private:
	const int total_health; //Useful for percentage calculations of hp
	const float mov_speed;
	const std::pair<float, float> forw_jump_speed;
	const std::pair<float, float> back_jump_speed;
	const float height_dmg;
	int actual_health;

	b2BodyDef body_def;
	b2PolygonShape body_shape;
	b2FixtureDef fixture_def;

public:
	Worm(Stage& stage
		, const int x
		, const int y
		, const int angle_rad
		, const int longitude
		, const int height
		, const float density
		, const float restitution
		, const int health
		, const float mov_speed
		, const std::pair<float, float> forw_jump_speed
		, const std::pair<float, float> back_jump_speed
		, const float height_dmg);

	void use(Usable& usable);
};

#endif
