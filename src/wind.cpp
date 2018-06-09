#include "movable.h"
#include "wind.h"
#include <stdlib.h>
#include <time.h> 
#include <Box2D/Box2D.h>

Wind::Wind() {
	//Initialize random
	this->direction = 0;
	this->change_wind();
}

void Wind::change_wind() {
	srand (time(NULL));

	float r = static_cast<float>(rand())/static_cast<float>(RAND_MAX);

	this->wind_speed = r * (MAX_WIND_SPEED - MIN_WIND_SPEED) + MIN_WIND_SPEED;

	this->direction = rand() % 2;
}

void Wind::apply(Movable* movable) {
	if (movable->is_affected_by_wind()) {
		b2Body* body = movable->get_body();
		b2Vec2 pos = body->GetWorldCenter();

		if (this->direction == 0)
			movable->get_body()->ApplyForce(b2Vec2(this->wind_speed, 0), pos);
		else if (this->direction == 1) {
			movable->get_body()->ApplyForce(b2Vec2(-this->wind_speed, 0), pos);
		}
	}
}