#ifndef THROWABLE_H
#define THROWABLE_H

#include "movable.h"
#include <Box2D/Box2D.h>

class Throwable : public Movable {

public:
	Throwable(Stage& stage
	, const b2Vec2& pos
	, const b2Vec2& velocity
	, const int longitude
	, const int height
	, const float density
	, const float restitution
	, const float max_dmg);
};

#endif
