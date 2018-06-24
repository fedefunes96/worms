#ifndef WIND_H
#define WIND_H

#include "movable.h"
#include "Box2D/Box2D.h"

#define MIN_WIND_SPEED 0.1
#define MAX_WIND_SPEED 1.0

class Wind {
private:
	float min_wind_speed;
	float max_wind_speed;

	float wind_speed;
	int direction;

public:
	Wind(const float min_wind_speed, const float max_wind_speed);

	void set_wind_limits(const float min_wind_speed, const float max_wind_speed);
	float get_wind_speed();

	void change_wind();
	void apply(Movable* movable);
};

#endif
