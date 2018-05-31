#include "worm.h"
#include <vector>
#include <utility>
#include "movable.h"
#include "stage.h"
#include <Box2D/Box2D.h>
#include <string>
#include "sensor.h"

int Worm::id_worms = 0;

Worm::Worm(Stage& stage
	, const int id
	, const int x
	, const int y
	, const float angle_rad
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

	//Set a sensor at the floor of the body
	//Barely showing
	this->sensor_for_jump.add_at_position(this->body
										, b2Vec2(0, -height*0.85)
										, longitude
										, height*0.1);

	this->actual_health = health;
	this->facing_direction = NONE;
	this->actual_velocity.Set(0, 0);
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
	//Mutex in here (1)
	float32 angle = this->body->GetAngle();

	switch (mdirect) {
		case RIGHT: {
			this->actual_velocity.Set(mov_speed*cos(angle), mov_speed*sin(angle));
			this->facing_direction = RIGHT;
			break;
		}
		case LEFT: {
			this->actual_velocity.Set(-mov_speed*cos(angle), mov_speed*sin(angle));
			this->facing_direction = LEFT;
			break;
		}	
		case JUMP_FORW: {
			this->actual_velocity.Set(forw_jump_speed.first, forw_jump_speed.second);	
			break;
		}
		case JUMP_BACK: {
			this->actual_velocity.Set(-back_jump_speed.first, back_jump_speed.second);				
			break;
		}										
		case NONE: {
			this->actual_velocity.Set(0, 0);
			break;
		}
	}
}

void Worm::move_step() {
	//Need mutex (1)
	if (this->is_on_ground()) {
		this->body->SetLinearVelocity(this->actual_velocity); 
	}
}

bool Worm::is_on_ground() {
	return this->sensor_for_jump.get_number_colisions() > 0;
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

/*void Worm::start_contacting(Ubicable* ubicable) {
	ubicable->colision(*this);
}*/

void Worm::start_contacting() {
	//Do nothing
}

void Worm::stop_contacting() {
	//Do nothing
}

/*void Worm::colision(Girder& girder) {
	//Do nothing
}

void Worm::colision(Worm& worm) {
	//Do nothing
}

void Worm::colision(Throwable& throwable) {
	//Do nothing
}*/