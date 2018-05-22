#include "throwable.h"
#include "movable.h"
#include <Box2D/Box2D.h>
#include "stage.h"
#include <cmath>
#include "explosion.h"
#include <string>

Throwable::Throwable(Stage& stage
	, const int x
	, const int y
	, const int angle_rad
	, const b2Vec2& velocity
	, const int longitude
	, const int height
	, const float restitution
	, const float max_dmg)
	: Movable(stage
		, x
		, y
		, angle_rad
		, longitude
		, height
		, restitution)
	, max_dmg(max_dmg) {

	//b2Vec2 vel(cos(angle_rad), sin(angle_rad));

	this->body->SetUserData(this);
	//this->body->SetLinearVelocity(velocity);
	this->body->ApplyLinearImpulse(velocity, this->body->GetWorldCenter());
}

void Throwable::explode() {
	//Explode in place
	Explosion explosion(this->stage
		, this->body->GetPosition()
		, 10.0);

	//Now i dissapear
	this->delete_myself();
}

//Whatever i hit, i must explode
void Throwable::colision(Movable& movable_obj) {
	this->explode();
}

void Throwable::colision(Static& static_obj) {
	this->explode();
}

std::string Throwable::get_type() {
	return THROWABLE_TYPE;
}
