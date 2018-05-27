#include "girder.h"
#include "ubicable.h"
#include "stage.h"
#include <string>

int Girder::id_girders = 0;

Girder::Girder(Stage& stage, const int x, const int y, const float angle_rad
, const int longitude, const int height) : stage(stage), id_obj(id_girders++) {
	b2BodyDef body_def;
	b2PolygonShape body_shape;
	b2FixtureDef fixture_def;

	body_def.type = b2_staticBody;
	body_def.position.Set(x, y);
	body_def.angle = angle_rad;

	body_shape.SetAsBox(longitude, height);

	fixture_def.shape = &(body_shape);

	this->body = stage.insert(&body_def);
	this->body->SetUserData(this); 

	this->fixture = this->body->CreateFixture(&fixture_def);		
	this->fixture->SetUserData(this);	
}

std::string Girder::get_type() {
	return GIRDER_TYPE;
}

void Girder::delete_myself() {
	this->stage.remove(this->body);
}

void Girder::start_contacting(Ubicable* ubicable) {
	ubicable->colision(*this);
}

void Girder::colision(Girder& girder) {
	//Do nothing
}

void Girder::colision(Worm& worm) {
	//Do nothing
}

void Girder::colision(Throwable& throwable) {
	//Do nothing
}

int Girder::get_id() {
	return this->id_obj;
}