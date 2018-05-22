/*#include "ubicable.h"
#include "stage.h"

Ubicable::Ubicable(Stage& stage) 
 : stage(stage) {}

void Ubicable::delete_myself() {
	this->stage.remove(*this);
}*/

/*void Ubicable::ubicar() {
	b2BodyDef* body_def = this->create_body_def();
	b2FixtureDef* fixture_def = this->create_fixture_def();

	this->body = this->stage.get_world().CreateBody(body_def);

	this->body->CreateFixture(fixture_def);	
}*/

/*b2Vec2 Ubicable::get_position() {
	return body->GetPosition();
}*/