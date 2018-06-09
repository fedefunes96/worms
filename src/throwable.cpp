#include "throwable.h"
#include "movable.h"
#include <Box2D/Box2D.h>
#include "stage.h"
#include <cmath>
#include "explosion.h"
#include <string>
#include "worm.h"
#include <iostream>
#include "query_callback.h"

int Throwable::id_throwables = 0;

Throwable::Throwable(Stage& stage
	, Worm* owner
	, const float x
	, const float y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const float max_pushback
	, const float radius_expl)
	: Movable(x, y)
	, stage(stage)
	, owner(owner)
	, id_obj(id_throwables++)
	, x(x)
	, y(y)
	, angle_rad(angle_rad)
	, velocity(velocity)
	, radius(radius)
	, restitution(restitution)
	, max_dmg(max_dmg)
	, max_pushback(max_pushback)
	, radius_expl(radius_expl) {

	this->dead = false;
	this->stop_collide_owner = false;
}

void Throwable::explode() {
	//Explode in place
	Explosion explosion(this->stage
		, this->body->GetPosition()
		, this->radius_expl
		, this->max_dmg);

	//Now i dissapear
	this->dead = true;
}

void Throwable::create_myself(b2World& world) {
	b2BodyDef body_def;
	b2CircleShape body_shape;
	b2FixtureDef fixture_def;

	body_def.type = b2_dynamicBody;
	body_def.position.Set(x, y);
	body_def.angle = angle_rad;

	body_shape.m_radius = radius;
	body_shape.m_p.Set(0, 0);

	fixture_def.shape = &(body_shape);
	fixture_def.density = 1.0;
	fixture_def.restitution = restitution;

	this->body = world.CreateBody(&body_def);
	this->body->SetUserData(this);

	b2Fixture* fixture = this->body->CreateFixture(&fixture_def);		
	fixture->SetUserData(this);

	this->body->ApplyLinearImpulse(velocity, this->body->GetWorldCenter());
}

void Throwable::delete_myself(b2World& world) {
	world.DestroyBody(this->body);
}

/*void Throwable::start_contacting(Ubicable* ubicable) {
	ubicable->colision(*this);
}*/
//Whatever i hit, i must explode
void Throwable::start_contacting(b2Contact* contact) {
	if (!this->dead)
		this->explode();
	//printf("Contact %0.1f %0.1f\n", this->body->GetPosition().x, this->body->GetPosition().y);
}

void Throwable::stop_contacting(Ubicable* ubicable) {
	//Do nothing
}

void Throwable::stop_contacting(Worm* worm) {

}

//Whatever i hit, i must explode
/*void Throwable::colision(Girder& girder) {
	this->explode();
}

void Throwable::colision(Worm& worm) {
	this->explode();
}

void Throwable::colision(Throwable& throwable) {
	this->explode();
}*/

int Throwable::get_id() {
	return this->id_obj;
}

void Throwable::move_step(float32 time_step) {
	//Dont move!
	//Just rotate
	b2Vec2 actual_pos = this->body->GetPosition();
	b2Vec2& last_pos = this->get_position();

	if (actual_pos.x == last_pos.x && actual_pos.y == last_pos.y) {
		this->body->SetTransform(actual_pos, this->angle_rad);
	} else {
		float32 angle = atan2(actual_pos.y - last_pos.y, actual_pos.x - last_pos.x);
		if(angle < 0){
			angle +=2*b2_pi;
		}
		this->body->SetTransform(actual_pos, angle);
	}
}

b2Body* Throwable::get_body() {
	return this->body;
}

bool Throwable::im_dead() {
	return this->dead;
}

void Throwable::force_death() {
	this->dead = true;
}

bool Throwable::should_collide_with(Ubicable* ubicable) {
	return ubicable->should_collide_with(this);
}
	
bool Throwable::should_collide_with(Girder* girder) {
	return true;
}

//bool Throwable::should_collide_with(Worm* worm) {
	//if (worm->get_id() == this->owner->get_id() && !stop_collide_owner) {
		/*QueryCallback queryCallback;
		b2AABB aabb;
		aabb.lowerBound = pos - b2Vec2(this->radius, this->radius);
		aabb.upperBound = pos + b2Vec2(this->radius, this->radius);
		this->stage.get_world().QueryAABB(&queryCallback, aabb);
		  
		if (queryCallback.foundBodies.size() > 0)	
			return false;*/
	//}

	/*if (!this->stop_collide_owner) {
		QueryCallback queryCallback;
		b2AABB aabb;

		b2Vec2 pos = this->body->GetPosition();

		aabb.lowerBound = pos - b2Vec2(this->radius, this->radius);
		aabb.upperBound = pos + b2Vec2(this->radius, this->radius);
		this->stage.get_world().QueryAABB(&queryCallback, aabb);

		if (queryCallback.foundBodies.size() - 1 > 0)	{
			//printf("Inside worm: %d\n", (int) queryCallback.foundBodies.size());
			return false;	
		} else {
			printf("Stop colliding worm\n");
			this->stop_collide_owner = true;
			return true;
		}
	}*/
bool Throwable::should_collide_with(Worm* worm) {
	if (worm->get_id() == this->owner->get_id()) {
		QueryCallback queryCallback;
		b2AABB aabb;

		b2Vec2 pos = this->body->GetPosition();

		aabb.lowerBound = pos - b2Vec2(this->radius, this->radius);
		aabb.upperBound = pos + b2Vec2(this->radius, this->radius);
		this->stage.get_world().QueryAABB(&queryCallback, aabb);

		//Minus 1 because it'll count the throwable
		if (queryCallback.foundBodies.size() - 1 > 0) 
			return false;
	}

	return true;
}

bool Throwable::should_collide_with(Sensor* sensor) {
	return false;
}

bool Throwable::should_collide_with(Throwable* throwable) {
	//Don't collide with other throwables
	return false;
}
