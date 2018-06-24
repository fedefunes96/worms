#ifndef EXPLOTION_H
#define EXPLOTION_H

#include "Box2D/Box2D.h"
#include "stage.h"

#define MAX_PUSHBACK 6.0

class Explosion {
public:
	Explosion(Stage& stage, const b2Vec2& pos, const float radius, const float max_dmg);
};

#endif
