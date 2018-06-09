#ifndef DELAYED_THROWABLE_H
#define DELAYED_THROWABLE_H

#include "throwable.h"
#include <Box2D/Box2D.h>

#define SECOND_IN_MILLISECOND 1000

class DelayedThrowable : public Throwable {
private:
	int counter;
	float conversor;
protected:
	virtual void explode() override;
public:
	DelayedThrowable(Stage& stage
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
	, const int time);

	virtual std::string get_type() = 0;
	virtual bool is_affected_by_wind() = 0;
	virtual void move_step(float32 time_step) override;
};

#endif
