#include "movable.h"
#include "ubicable.h"
#include "stage.h"
#include <Box2D/Box2D.h>

Movable::Movable(Stage& stage
	, const int x
	, const int y
	, const int angle_rad
	, const int longitude
	, const int height
	, const float restitution)
	: stage(stage) {
	this->body_def.type = b2_dynamicBody;
	this->body_def.position.Set(x, y);
	this->body_def.angle = angle_rad;

	this->body_shape.SetAsBox(longitude, height);

	this->fixture_def.shape = &(this->body_shape);
	this->fixture_def.density = 1.0;
	this->fixture_def.restitution = restitution;

	//this->body = stage.get_world().CreateBody(&this->body_def);
	this->body = stage.insert(&this->body_def);

	//this->body->SetUserData(this); 

	this->fixture = this->body->CreateFixture(&this->fixture_def);		
	
	this->fixture->SetUserData(this);

  	//this->ubicar();
}

void Movable::delete_myself() {
	this->stage.remove(this->body);
}

void Movable::start_contacting(Ubicable* ubicable) {
	ubicable->colision(*this);
}

void Movable::colision(Movable& movable_obj) {
	//Do nothing
}

void Movable::colision(Static& static_obj) {
	//Do nothing
}

b2Vec2 Movable::get_position() {
	return this->body->GetPosition();
}
/*b2BodyDef* Movable::create_body_def() {
	return &this->body_def;
}

b2FixtureDef* Movable::create_fixture_def() {
	return &this->fixture_def;
}*/