#ifndef UBICABLE_H
#define UBICABLE_H

#include <Box2D/Box2D.h>
#include "stage.h"
//#include "movable.h"
//#include "static.h"

class Movable;
class Static;

class Ubicable {
protected:
	b2Body* body;
	Stage& stage;

	void ubicar();

	virtual b2BodyDef* create_body_def() = 0;
	virtual b2FixtureDef* create_fixture_def() = 0;	
public:
	Ubicable(Stage& stage);

	virtual void start_contacting(Ubicable* ubicable) = 0;

	b2Vec2 get_position();

	//Each ubicable needs to know what to do
	//when it collides with another object
	//General cases - Dont do anything
	virtual void colision(Movable& movable_obj) = 0;
	virtual void colision(Static& static_obj) = 0;
	//Special cases
	//virtual void colision(Water& movable);
};

#endif
