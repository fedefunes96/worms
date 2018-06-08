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

void Sensor::delete_myself(b2World& world) {
	//This object doesn't exist in the stage
}

void Sensor::start_contacting(b2Contact* contact) {
	this->object_count++;

	//printf("Colliding\n");

	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	/*float angle = atan2(worldManifold.normal.y, worldManifold.normal.x) - b2_pi/2;

	float angle_for_mov = angle;

	if (b2_pi/4 <= fabs(angle_for_mov) &&  fabs(angle_for_mov) < b2_pi/2) {
		this->worm.set_gravity(DEFAULT_GRAVITY);
		this->worm.set_slide(true);
	} else if (0 <= fabs(angle_for_mov) && fabs(angle_for_mov) < b2_pi/4) {
		this->worm.set_gravity(b2Vec2(0, 0));
		this->worm.set_slide(false);
	} else {
		this->worm.set_gravity(DEFAULT_GRAVITY);
		this->worm.set_slide(false);
	}	*/
}

void Sensor::stop_contacting(Ubicable* ubicable) {
	this->object_count--;

	this->worm.set_gravity(DEFAULT_GRAVITY);
	this->worm.set_slide(false);
}

void Sensor::stop_contacting(Worm* worm) {
	//Do nothing
	//Count once
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
	return true;
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

void Sensor::pre_solve_contact(b2Contact* contact, const b2Manifold* oldManifold) {
	/*b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	printf("X: %0.1f Y: %0.1f\n", worldManifold.normal.x, worldManifold.normal.y);*/
}