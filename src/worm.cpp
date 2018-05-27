#include "worm.h"
#include <vector>
#include <utility>
#include "ubicable.h"
#include "stage.h"
#include <Box2D/Box2D.h>
#include <string>

int Worm::id_worms = 0;

Worm::Worm(Stage& stage
	, const int id
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
	: stage(stage)
	, id(id)
	, id_obj(id_worms++)
	, total_health(health)
	, mov_speed(mov_speed)
	, forw_jump_speed(forw_jump_speed)
	, back_jump_speed(back_jump_speed)
	, height_dmg(height_dmg)
	, longitude(longitude)
	, height(height) {
	b2BodyDef body_def;
	b2PolygonShape body_shape;
	b2FixtureDef fixture_def;

	body_def.type = b2_dynamicBody;
	body_def.position.Set(x, y);
	body_def.angle = angle_rad;

	body_shape.SetAsBox(longitude, height);

	fixture_def.shape = &(body_shape);
	fixture_def.density = 1.0;
	fixture_def.restitution = restitution;

	this->body = stage.insert(&body_def);
	this->body->SetUserData(this);

	this->fixture = this->body->CreateFixture(&fixture_def);		
	this->fixture->SetUserData(this);

	this->actual_health = health;
	this->facing_direction = NONE;
}

void Worm::receive_dmg(int damage) {
	if (this->actual_health - damage <= 0) {
		this->actual_health = 0;
		this->delete_myself();
	} else {
		this->actual_health -= damage;
	}
}

int Worm::get_health() {
	return this->actual_health;
}

void Worm::add_health(int health) {
	this->actual_health += health;
}

void Worm::start_moving(MoveDirection mdirect) {
	if (this->facing_direction != mdirect) {
		this->facing_direction = mdirect;

		float32 angle = this->body->GetAngle();

		switch (mdirect) {
			case RIGHT: {
				this->actual_velocity = b2Vec2(mov_speed*cos(angle), mov_speed*sin(angle));
				break;
			}
			case LEFT: {
				this->actual_velocity = b2Vec2(-mov_speed*cos(angle), mov_speed*sin(angle));
				break;
			}	
			case JUMP_FORW: {
				
				break;
			}
			case JUMP_BACK: {
				
				break;
			}										
			case NONE: break;
		}
	}
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

std::string Worm::get_type() {
	return WORM_TYPE;
}

int Worm::get_id() {
	return this->id_obj;
}

void Worm::delete_myself() {
	this->stage.remove(this->body);
}

void Worm::start_contacting(Ubicable* ubicable) {
	ubicable->colision(*this);
}

void Worm::colision(Girder& girder) {
	//Do nothing
}

void Worm::colision(Worm& worm) {
	//Do nothing
}

void Worm::colision(Throwable& throwable) {
	//Do nothing
}