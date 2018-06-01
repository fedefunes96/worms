#include "girder.h"
#include "ubicable.h"
#include "stage.h"
#include <string>

int Girder::id_girders = 0;

Girder::Girder(Stage& stage
	, const int x
	, const int y
	, const float angle_rad
	, const int longitude
	, const int height) 
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

void Girder::start_contacting() {
	//Do nothing
}

void Girder::stop_contacting() {
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