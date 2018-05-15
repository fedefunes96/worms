#ifndef MOVABLE_H
#define MOVABLE_H

#include "ubicable.h"
#include "static.h"
#include "stage.h"
#include <Box2D/Box2D.h>

class Movable : public Ubicable {
private:
	b2BodyDef body_def;
	b2PolygonShape body_shape;
	b2FixtureDef fixture_def;

	virtual b2BodyDef* create_body_def() override;
	virtual b2FixtureDef* create_fixture_def() override;	
protected:
	Movable(Stage& stage
		, const int x
		, const int y
		, const int angle_rad
		, const int longitude
		, const int height
		, const float density
		, const float restitution);

	virtual void start_contacting(Ubicable* ubicable) override;

	void colision(Movable& movable_obj);
	void colision(Static& static_obj);
	//void colision(Floor& floor);
};

#endif
