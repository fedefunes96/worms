#include "sensor.h"
#include "ubicable.h"
#include <Box2D/Box2D.h>
#include "worm.h"

Sensor::Sensor(Worm& worm)
 : worm(worm) {
	this->object_count = 0;
}

void Sensor::add_at_position(b2Body* body, b2Vec2 pos, float longitude, float height) {
	b2PolygonShape body_shape;
	b2FixtureDef fixture_def;

	body_shape.SetAsBox(longitude, height, pos, 0);

	fixture_def.shape = &(body_shape);
	fixture_def.density = 0.1;
	
    //fixture_def.isSensor = true;

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

void Sensor::delete_myself(b2World& world) {
	//This object doesn't exist in the stage
}

void Sensor::start_contacting(b2Contact* contact) {
	this->object_count++;

	//printf("Colliding\n");

	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	//printf("%0.1f %0.1f\n", worldManifold.normal.y, worldManifold.normal.x);

	float angle = atan2(worldManifold.normal.y, worldManifold.normal.x) - b2_pi/2;

	//this->worm.set_angle(angle);

	if (b2_pi/4 <= fabs(angle) && fabs(angle) < b2_pi/2) {
		this->worm.set_gravity(DEFAULT_GRAVITY);
		this->worm.set_slide(true);
		this->worm.set_velocity(b2Vec2(0, 0));
	} else if (0 <= fabs(angle) && fabs(angle) < b2_pi/4) {
		this->worm.set_gravity(b2Vec2(0, 0));
		this->worm.set_slide(false);
		this->worm.set_angle(angle);
	} else {
		this->worm.set_gravity(DEFAULT_GRAVITY);
		this->worm.set_slide(false);	
		//this->worm.set_angle(angle);
	}
}

void Sensor::stop_contacting(b2Contact* contact) {
	this->object_count--;

	//Only set gravity if its in the air
	if (!this->object_count) {
		this->worm.set_gravity(DEFAULT_GRAVITY);
		this->worm.set_slide(false);
	}
}

b2Body* Sensor::get_body() {
	b2Body* b = nullptr;
	return b;
}

bool Sensor::im_dead() {
	return false;
}

void Sensor::force_death() {

}

bool Sensor::should_collide_with(Ubicable* ubicable) {
	return ubicable->should_collide_with(this);
}
	
bool Sensor::should_collide_with(Girder* girder) {
	return true;
}

bool Sensor::should_collide_with(Worm* worm) {
	return false;
}

bool Sensor::should_collide_with(Throwable* throwable) {
	return false;
}

bool Sensor::should_collide_with(Sensor* sensor) {
	return false;
}

void Sensor::pre_solve_contact(b2Contact* contact, const b2Manifold* oldManifold) {

}