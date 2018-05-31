#include "sensor.h"
#include "ubicable.h"
#include <Box2D/Box2D.h>

Sensor::Sensor() {
	this->object_count = 0;
}

void Sensor::add_at_position(b2Body* body, b2Vec2 pos, float longitude, float height) {
	b2PolygonShape body_shape;
	b2FixtureDef fixture_def;

	body_shape.SetAsBox(longitude, height*0.1, b2Vec2(0, -height*0.85), 0);

	fixture_def.shape = &(body_shape);
	fixture_def.density = 1.0;
	
    fixture_def.isSensor = true;

    b2Fixture* sensor = body->CreateFixture(&fixture_def);

    sensor->SetUserData(this);	
}

int Sensor::get_number_colisions() {
	return this->object_count;
}

std::string Sensor::get_type() {
	//This object doesn't exist in the stage
	return "";
}

int Sensor::get_id() {
	//This object doesn't exist in the stage
	return 0;
}

void Sensor::create_myself(b2World& world) {
	//This object doesn't exist in the stage
}	

void Sensor::delete_myself() {
	//This object doesn't exist in the stage
}

void Sensor::start_contacting() {
	this->object_count++;
}

void Sensor::stop_contacting() {
	this->object_count--;
}
