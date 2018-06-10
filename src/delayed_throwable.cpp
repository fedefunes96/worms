#include "throwable.h"
#include "delayed_throwable.h"
#include <Box2D/Box2D.h>

DelayedThrowable::DelayedThrowable(Stage& stage
	, Worm* owner
	, const float x
	, const float y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const float max_pushback
	, const float radius_expl
	, const int time)
	: Throwable(stage
		, owner
		, x
		, y
		, angle_rad
		, velocity
		, radius
		, restitution
		, max_pushback
		, max_dmg
		, radius_expl)
	, counter(time) {
		this->conversor = 0;
}

void DelayedThrowable::start_contacting(b2Contact* contact) {
	if (!this->dead && this->counter == 0)
		this->explode();
	//printf("Contact %0.1f %0.1f\n", this->body->GetPosition().x, this->body->GetPosition().y);
}

void DelayedThrowable::move_step(float32 time_step) {
	//This is called once per time_step, so... (ms unit)
	if (this->counter > 0) {
		this->conversor++;

		if (this->conversor == SECOND_IN_MILLISECOND/time_step) {
			this->counter--;
			this->conversor = 0;
		}
	}
}