#include "girder.h"
#include "ubicable.h"
#include "stage.h"
#include <string>

int Girder::id_girders = 0;

Girder::Girder(Stage& stage
	, const float x
	, const float y
	, const float angle_rad
	, const float longitude
	, const float height) 
	: stage(stage)
	, id_obj(id_girders++) 
	, x(x)
	, y(y)
	, angle_rad(angle_rad)
	, longitude(longitude)
	, height(height) {

}

std::string Girder::get_type() {
	return GIRDER_TYPE;
}

void Girder::create_myself(b2World& world) {
	b2BodyDef body_def;
	b2PolygonShape body_shape;
	b2FixtureDef fixture_def;

	body_def.type = b2_staticBody;
	body_def.position.Set(x, y);
	body_def.angle = angle_rad;

	body_shape.SetAsBox(longitude, height);

	fixture_def.shape = &(body_shape);

	this->body = world.CreateBody(&body_def);
	this->body->SetUserData(this); 

	b2Fixture* fixture = this->body->CreateFixture(&fixture_def);		
	fixture->SetUserData(this);
}

void Girder::delete_myself(b2World& world) {
	//this->stage.remove(this->body);
	world.DestroyBody(this->body);
}

void Girder::start_contacting(b2Contact* contact) {
	//Do nothing
}

void Girder::stop_contacting(b2Contact* contact) {
	//Do nothing
}

int Girder::get_id() {
	return this->id_obj;
}

b2Body* Girder::get_body() {
	return this->body;
}

bool Girder::im_dead() {
	return false;
}

void Girder::force_death() {

}

bool Girder::should_collide_with(Ubicable* ubicable) {
	return ubicable->should_collide_with(this);
}
	
bool Girder::should_collide_with(Girder* girder) {
	//Girder's won't collide with girder's
	return false;
}

bool Girder::should_collide_with(Worm* girder) {
	return true;
}

bool Girder::should_collide_with(Throwable* girder) {
	return true;
}

bool Girder::should_collide_with(Sensor* sensor) {
	return true;
}
