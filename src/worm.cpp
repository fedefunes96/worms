#include "worm.h"
#include <vector>
#include <utility>
#include "movable.h"
#include <Box2D/Box2D.h>
#include <string>

Worm::Worm(Stage& stage
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
	, const float height_dmg)
	: Movable(stage
			, x
			, y
			, angle_rad
			, longitude
			, height
			, restitution)
	, total_health(health)
	, mov_speed(mov_speed)
	, forw_jump_speed(forw_jump_speed)
	, back_jump_speed(back_jump_speed)
	, height_dmg(height_dmg)
	, longitude(longitude)
	, height(height) {

	this->actual_health = health;
	this->body->SetUserData(this);
}

void Worm::receive_dmg(int damage) {
	if (this->actual_health - damage <= 0) {
		this->delete_myself();
	} else {
		this->actual_health -= damage;
	}
}

int Worm::get_health() {
	return this->actual_health;
}

void Worm::move_left() {
	this->body->SetTransform(body->GetPosition(), b2_pi);
	this->body->SetLinearVelocity(b2Vec2(-mov_speed, 0));
}

void Worm::move_right() {
	this->body->SetTransform(body->GetPosition(), 0.0);
	this->body->SetLinearVelocity(b2Vec2(mov_speed, 0));
}

void Worm::jump_forw() {
	float32 angle = this->body->GetAngle();

	this->body->SetLinearVelocity(b2Vec2(back_jump_speed.first*cos(angle)
										, back_jump_speed.second));
}

void Worm::jump_back() {
	float32 angle = this->body->GetAngle();

	this->body->SetLinearVelocity(b2Vec2(forw_jump_speed.first*cos(angle)
										, forw_jump_speed.second));
}

void Worm::use(Usable& usable, const b2Vec2& dest) {
	/*b2Vec2 pos = this->body->GetPosition();

	float32 angle = atan2(dest.y - pos.y, dest.x - pos.x);

	b2Vec2 angle_vec(cos(angle), sin(angle));*/
	//usable.use();
}

void Worm::set_owner(const int player_id) {
	this->owner = player_id;
}

std::string Worm::get_type() {
	return WORM_TYPE;
}
