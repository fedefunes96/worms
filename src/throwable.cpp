#include "throwable.h"
#include "movable.h"
#include <Box2D/Box2D.h>
#include "stage.h"
#include <cmath>
#include "explosion.h"
#include <string>
#include "worm.h"

int Throwable::id_throwables = 0;

Throwable::Throwable(Stage& stage
	, Worm* owner
	, const int x
	, const int y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg)
	: stage(stage)
	, owner(owner)
	, id_obj(id_throwables++)
	, x(x)
	, y(y)
	, angle_rad(angle_rad)
	, velocity(velocity)
	, angular_velocity(angular_velocity)
	, radius(radius)
	, restitution(restitution)
	, max_dmg(max_dmg) {

	this->dead = false;
	this->stop_collide_owner = false;
}

void Throwable::explode() {
	//Explode in place
	Explosion explosion(this->stage
		, this->body->GetPosition()
		, this->radius
		, this->max_dmg);

	//Now i dissapear
	this->dead = true;
	printf("Explode\n");
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

	this->body->ApplyAngularImpulse(angular_velocity);
}

void Throwable::delete_myself(b2World& world) {
	world.DestroyBody(this->body);
}

/*void Throwable::start_contacting(Ubicable* ubicable) {
	ubicable->colision(*this);
}*/
//Whatever i hit, i must explode
void Throwable::start_contacting() {
	if (!this->dead)
		this->explode();
}

void Throwable::stop_contacting(Ubicable* ubicable) {
	//Do nothing
}

void Throwable::stop_contacting(Worm* worm) {
	if (worm->get_id() == this->owner->get_id() && !stop_collide_owner)
		this->stop_collide_owner = true;
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

bool Throwable::should_collide_with(Worm* worm) {
	if (worm->get_id() == this->owner->get_id() && !stop_collide_owner)
		return false;

	return true;
}

bool Throwable::should_collide_with(Throwable* throwable) {
	//Don't collide with other throwables
	return false;
}
