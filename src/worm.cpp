#include "worm.h"
#include <vector>
#include <utility>
#include "movable.h"
#include <Box2D/Box2D.h>

Worm::Worm(Stage& stage
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
	, const float height_dmg)
	: Movable(stage
			, x
			, y
			, angle_rad
			, longitude
			, height
			, density
			, restitution)
	, total_health(health)
	, mov_speed(mov_speed)
	, forw_jump_speed(forw_jump_speed)
	, back_jump_speed(back_jump_speed)
	, height_dmg(height_dmg) {

	this->actual_health = health;
}

void Worm::use(Usable& usable) {
	//usable.use();
}