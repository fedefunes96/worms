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
	, id_obj(id_worms++)
	, x(x)
	, y(y)
	, angle_rad(angle_rad)
	, restitution(restitution)
	, total_health(health)
	, mov_speed(mov_speed)
	, forw_jump_speed(forw_jump_speed)
	, back_jump_speed(back_jump_speed)
	, height_dmg(height_dmg)
	, longitude(longitude)
	, height(height) {

	this->actual_health = health;
	this->facing_direction = MoveDirection::RIGHT;
	this->move_direction = MoveDirection::NONE;
	this->actual_velocity.Set(0, 0);
	this->dead = true;
	this->jump_cooldown = 0;
}

void Worm::receive_dmg(int damage) {
	if (this->actual_health - damage <= 0) {
		this->actual_health = 0;
		this->dead = true;
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
	this->move_direction = mdirect;
}

void Worm::move_step(float32 time_step) {
	//Need mutex (1)
	//printf("Actual speed: %0.1f %0.1f\n", this->actual_velocity.x, this->actual_velocity.y);

	if (this->is_on_ground() && !this->jump_cooldown) {
		//printf("Im on ground\n");
		//printf("Actual speed: %0.1f %0.1f\n", this->actual_velocity.x, this->actual_velocity.y);	
		float32 angle = this->body->GetAngle();

		switch (this->move_direction) {
			case MoveDirection::RIGHT: {
				this->actual_velocity.Set(mov_speed*cos(angle)*time_step, mov_speed*sin(angle)*time_step);
				this->facing_direction = MoveDirection::RIGHT;
				break;
			}
			case MoveDirection::LEFT: {
				this->actual_velocity.Set(-mov_speed*cos(angle)*time_step, mov_speed*sin(angle)*time_step);
				this->facing_direction = MoveDirection::LEFT;
				break;
			}	
			case MoveDirection::JUMP_FORW: {
				if(this->facing_direction == MoveDirection::LEFT)
					this->actual_velocity.Set(-forw_jump_speed.first, forw_jump_speed.second);	
				else if (this->facing_direction == MoveDirection::RIGHT) {
					this->actual_velocity.Set(forw_jump_speed.first, forw_jump_speed.second);	
				}
				this->jump_cooldown = JUMP_COOLDOWN;
				break;
			}
			case MoveDirection::JUMP_BACK: {
				if(this->facing_direction == MoveDirection::LEFT)
					this->actual_velocity.Set(back_jump_speed.first, back_jump_speed.second);	
				else if (this->facing_direction == MoveDirection::RIGHT) {
					this->actual_velocity.Set(-back_jump_speed.first, back_jump_speed.second);	
				}	
				this->jump_cooldown = JUMP_COOLDOWN;			
				break;
			}										
			case MoveDirection::NONE: {
				this->actual_velocity.Set(0, 0);
				break;
			}
		}

		if (this->jump_cooldown > 0) {
			this->jump_cooldown--;
		}

		this->body->SetLinearVelocity(this->actual_velocity); 
	}
}

bool Worm::is_on_ground() {
	return this->sensor_for_jump.get_number_colisions() > 0;
}

void Worm::use(std::unique_ptr<Usable>& usable, const b2Vec2& dest, const std::vector<float>& params) {
	if (this->dead)
		return;

	b2Vec2 pos = this->body->GetPosition();

	usable->use(this->longitude, this->height, pos, dest, params);
}

std::string Worm::get_type() {
	return WORM_TYPE;
}

int Worm::get_id() {
	return this->id_obj;
}

void Worm::create_myself(b2World& world) {
	this->dead = false;

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

	this->body = world.CreateBody(&body_def);
	this->body->SetUserData(this);

	b2Fixture* fixture = this->body->CreateFixture(&fixture_def);		
	fixture->SetUserData(this);

	//Set a sensor at the floor of the body
	//Barely showing
	this->sensor_for_jump.add_at_position(body
										, b2Vec2(0, -height)
										, longitude
										, height*0.1);
}

void Worm::delete_myself(b2World& world) {
	world.DestroyBody(this->body);
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

b2Body* Worm::get_body() {
	return this->body;
}

bool Worm::im_dead() {
	return this->dead;
}

void Worm::force_death() {
	this->dead = true;
}