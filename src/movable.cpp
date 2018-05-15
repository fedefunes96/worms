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
	, const float density
	, const float restitution)
	: Ubicable(stage) {
	this->body_def.type = b2_dynamicBody;
	this->body_def.position.Set(x, y);
	this->body_def.angle = angle_rad;

	this->body_shape.SetAsBox(longitude, height);

	this->fixture_def.shape = &(this->body_shape);
	this->fixture_def.density = density;
	this->fixture_def.restitution = restitution;
	
  	this->ubicar();
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

b2BodyDef* Movable::create_body_def() {
	return &this->body_def;
}

b2FixtureDef* Movable::create_fixture_def() {
	return &this->fixture_def;
}