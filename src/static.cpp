#include "static.h"
#include "movable.h"
#include "stage.h"

Static::Static(Stage& stage, const int x, const int y, const int angle_rad
, const int longitude, const int height) 
 : stage(stage) {
	this->body_def.type = b2_staticBody;
	this->body_def.position.Set(x, y);
	this->body_def.angle = angle_rad;

	this->body_shape.SetAsBox(longitude, height);

	this->fixture_def.shape = &(this->body_shape);

	//this->body = stage.get_world().CreateBody(&this->body_def);
	this->body = stage.insert(&this->body_def);
	//this->body->SetUserData(this); 

	//this->body->CreateFixture(&this->fixture_def);
	this->fixture = this->body->CreateFixture(&this->fixture_def);		
	
	this->fixture->SetUserData(this);
  	//this->ubicar();
}

void Static::delete_myself() {
	this->stage.remove(this->body);
}

void Static::start_contacting(Ubicable* ubicable) {
	ubicable->colision(*this);
}

void Static::colision(Movable& movable_obj) {
	//Do nothing
}

void Static::colision(Static& static_obj) {
	//Do nothing
}

b2Vec2 Static::get_position() {
	return this->body->GetPosition();
}
/*b2BodyDef* Static::create_body_def() {
	return &this->body_def;
}

b2FixtureDef* Static::create_fixture_def() {
	return &this->fixture_def;
}*/