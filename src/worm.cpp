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
	, const float x
	, const float y
	, const float angle_rad
	, const float longitude
	, const float height
	, const float restitution
	, const int health
	, const float mov_speed
	, const std::pair<float, float> forw_jump_speed
	, const std::pair<float, float> back_jump_speed
	, const float max_height_dmg
	, const float min_height_for_dmg)
	: Movable(x, y)
	, stage(stage)
	, id_obj(id_worms++)
	, x(x)
	, y(y)
	, angle_rad(angle_rad)
	, restitution(restitution)
	, total_health(health)
	, mov_speed(mov_speed)
	, forw_jump_speed(forw_jump_speed)
	, back_jump_speed(back_jump_speed)
	, max_height_dmg(max_height_dmg)
	, min_height_for_dmg(min_height_for_dmg)
	, longitude(longitude)
	, height(height) {

	this->actual_health = health;
	this->facing_direction = MoveDirection::RIGHT;
	this->move_direction = MoveDirection::NONE;
	this->actual_velocity.Set(0, 0);
	this->dead = true;
	this->jump_cooldown = 0;
	this->should_slide = false;

	this->last_position.Set(x, y);
}

void Worm::receive_dmg(int damage) {
	if (this->actual_health - damage <= 0) {
		this->actual_health = 0;
		this->dead = true;
	} else {
		this->actual_health -= damage;
	}
}

float Worm::get_longitude() {
	return this->longitude;
}

float Worm::get_height() {
	return this->height;
}

int Worm::get_health() {
	return this->actual_health;
}

void Worm::add_health(int health) {
	this->actual_health += health;
}

void Worm::start_moving(MoveDirection mdirect) {
	if (this->dead)
		return;

	std::lock_guard<std::mutex> lock(this->direction_m);

	this->move_direction = mdirect;

	if (this->is_on_ground() && !this->jump_cooldown) {
		//printf("Im on ground\n");
		//printf("Actual speed: %0.1f %0.1f\n", this->actual_velocity.x, this->actual_velocity.y);	
		float32 angle = this->body->GetAngle();

		switch (this->move_direction) {
			case MoveDirection::RIGHT: {
				this->actual_velocity.Set(mov_speed*cos(angle), mov_speed*sin(angle));
				this->facing_direction = MoveDirection::RIGHT;
				break;
			}
			case MoveDirection::LEFT: {
				this->actual_velocity.Set(-mov_speed*cos(angle), mov_speed*sin(angle));
				this->facing_direction = MoveDirection::LEFT;
				break;
			}	
			case MoveDirection::JUMP_FORW: {
				this->actual_velocity.Set(0, 0);
				this->body->SetLinearVelocity(this->actual_velocity);
				b2Vec2 impulse_speed;

				if(this->facing_direction == MoveDirection::LEFT) {
					impulse_speed.Set(-forw_jump_speed.first, forw_jump_speed.second);
				}
				else if (this->facing_direction == MoveDirection::RIGHT) {
					impulse_speed.Set(forw_jump_speed.first, forw_jump_speed.second);
				}
				this->body->ApplyLinearImpulse(impulse_speed, this->body->GetWorldCenter());
				this->jump_cooldown = JUMP_COOLDOWN;
				break;
			}
			case MoveDirection::JUMP_BACK: {
				this->actual_velocity.Set(0, 0);	
				this->body->SetLinearVelocity(this->actual_velocity);
				b2Vec2 impulse_speed;

				if(this->facing_direction == MoveDirection::LEFT) {
					impulse_speed.Set(back_jump_speed.first, back_jump_speed.second);
				}
				else if (this->facing_direction == MoveDirection::RIGHT) {
					impulse_speed.Set(-back_jump_speed.first, back_jump_speed.second);
				}
				this->body->ApplyLinearImpulse(impulse_speed, this->body->GetWorldCenter());
				this->jump_cooldown = JUMP_COOLDOWN;			
				break;
			}										
			case MoveDirection::NONE: {
				this->actual_velocity.Set(0, 0);
				break;
			}
		}
	}	
}

void Worm::set_slide(bool slide) {
	this->should_slide = slide;
}

void Worm::move_step(float32 time_step) {
	std::lock_guard<std::mutex> lock(this->direction_m);

	/*if (this->jump_cooldown > 0) {
		this->jump_cooldown--;
	} else {
		//this->body->SetLinearVelocity(this->actual_velocity);
	}*/

	if (this->is_on_ground()) {
		if (this->jump_cooldown == 0) {
			this->body->SetLinearVelocity(this->actual_velocity);
		}

		b2Vec2 actual_position = this->body->GetPosition();

		float fall_height = last_position.y - actual_position.y;

		if (fall_height >= this->min_height_for_dmg) {
			if (fall_height >= max_height_dmg)
				this->receive_dmg(max_height_dmg);
			else
				this->receive_dmg(fall_height);
		}

		this->last_position = actual_position;
	}

	if(this->jump_cooldown > 0) {
		this->jump_cooldown--;
	}
}

void Worm::pre_solve_contact(b2Contact* contact, const b2Manifold* oldManifold) {
	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	//printf("X: %0.1f Y: %0.1f\n", worldManifold.normal.x, worldManifold.normal.y);
	
	/*b2Vec2 a = b2Mul(b2Mat22((desiredSlopeAngle - 90.0) * (b2_pi / 180.0)), b2Vec2(0.0, 1.0));
	b2Vec2 b = b2Vec2(-a.x, a.y);

	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	this->should_slide = (b2Dot(a, worldManifold.normal) < 0.0) || (b2Dot(b,  worldManifold.normal) < 0.0);

	if(this->should_slide) {
		this->set_gravity(DEFAULT_GRAVITY);
		printf("Angle contact: %0.2f\n", b2Dot(a, worldManifold.normal));
		printf("Angle contact: %0.2f\n", b2Dot(b, worldManifold.normal));
	} else {
		this->set_gravity(b2Vec2(0.0, 0.0));
	}*/
}

bool Worm::is_on_ground() {
	return this->sensor_for_jump.get_number_colisions() > 0;
}

void Worm::use(std::unique_ptr<Usable>& usable, const b2Vec2& dest, const std::vector<float>& params) {
	if (this->dead)
		return;

	//b2Vec2 pos = this->body->GetPosition();

	usable->use(this, dest, params);
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
	body_def.fixedRotation = true;

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
										, longitude*0.9
										, height*0.1);

}

void Worm::delete_myself(b2World& world) {
	world.DestroyBody(this->body);
}

/*void Worm::start_contacting(Ubicable* ubicable) {
	ubicable->colision(*this);
}*/

void Worm::start_contacting() {
	
}

void Worm::stop_contacting(Ubicable* ubicable) {
	this->set_gravity(DEFAULT_GRAVITY);

	ubicable->stop_contacting(this);
}

void Worm::stop_contacting(Worm* worm) {
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

bool Worm::is_affected_by_wind() {
	return false;
}

bool Worm::should_collide_with(Ubicable* ubicable) {
	return ubicable->should_collide_with(this);
}
	
bool Worm::should_collide_with(Girder* girder) {
	return true;
}

bool Worm::should_collide_with(Worm* worm) {
	//Dont collide with other worms
	return false;
}

bool Worm::should_collide_with(Throwable* throwable) {
	return true;
}
