#ifndef WORM_H
#define WORM_H

#include <vector>
#include <utility>
#include "usable.h"
#include "movable.h"
#include <Box2D/Box2D.h>
#include <string>

#define WORM_TYPE "Worm"

class Worm : public Movable {
private:
	const int total_health; //Useful for percentage calculations of hp
	const float mov_speed;
	const std::pair<float, float> forw_jump_speed;
	const std::pair<float, float> back_jump_speed;
	const float height_dmg;
	const int longitude;
	const int height;
	int actual_health;
	int owner;

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
		, const float restitution
		, const int health
		, const float mov_speed
		, const std::pair<float, float> forw_jump_speed
		, const std::pair<float, float> back_jump_speed
		, const float height_dmg);

	virtual std::string get_type() override;

	int get_health();
	void receive_dmg(int damage);

	void move_left();
	void move_right();
	void jump_forw();
	void jump_back();

	void use(Usable& usable, const b2Vec2& dest);	
	void set_owner(const int player_id);
};

#endif
