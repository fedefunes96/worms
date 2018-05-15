#ifndef FLOOR_H
#define FLOOR_H

#include <Box2D/Box2D.h>

class Floor {

public:
	Floor(b2World& world
		, const int x
		, const int y
		, const int angle
		, const int longitude
		, const int height);	
};

#endif
