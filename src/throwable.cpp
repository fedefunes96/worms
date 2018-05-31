#include "throwable.h"
#include "movable.h"
#include <Box2D/Box2D.h>
#include "stage.h"
#include <cmath>
#include "explosion.h"
#include <string>

int Throwable::id_throwables = 0;

Throwable::Throwable(Stage& stage
	, const int x
	, const int y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg)
	: stage(stage)
	, id_obj(id_throwables++)
	, x(x)
	, y(y)
	, angle_rad(angle_rad)
	, velocity(velocity)
	, angular_velocity(angular_velocity)
	, radius(radius)
	, restitution(restitution)
	, max_dmg(max_dmg) {

	/*b2BodyDef body_def;
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

	this->body = stage.insert(&body_def);
	this->body->SetUserData(this);

	this->fixture = this->body->CreateFixture(&fixture_def);		
	this->fixture->SetUserData(this);*/

	stage.insert(this);
}

void Throwable::explode() {
	//Explode in place
	Explosion explosion(this->stage
		, this->body->GetPosition()
		, 10.0);

	//Now i dissapear
	this->delete_myself();
}

std::string Throwable::get_type() {
	return THROWABLE_TYPE;
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
}

void Throwable::delete_myself() {
	this->stage.remove(this->body);
}

/*void Throwable::start_contacting(Ubicable* ubicable) {
	ubicable->colision(*this);
}*/
//Whatever i hit, i must explode
void Throwable::start_contacting() {
	this->explode();
}

void Throwable::stop_contacting() {
	//Do nothing
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

void Throwable::move_step() {
	//Dont move!
		/*this->body->ApplyLinearImpulse(velocity, this->body->GetWorldCenter());

		this->body->ApplyAngularImpulse(angular_velocity);*/

}
