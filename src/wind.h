#ifndef WIND_H
#define WIND_H

#include "movable.h"
#include <Box2D/Box2D.h>

#define MIN_WIND_SPEED 0.1
#define MAX_WIND_SPEED 1.0

class Wind {
private:
	float wind_speed;
	int direction;

public:
	Wind();

	void change_wind();
	void apply(Movable* movable);
};

#endif
