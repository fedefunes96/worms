#ifndef MOVABLE_H
#define MOVABLE_H

#include "ubicable.h"
#include "static.h"
//#include "stage.h"
#include <Box2D/Box2D.h>
#include <string>

class Stage;

class Movable : public Ubicable {
protected:
	b2Body* body;
	b2Fixture* fixture;
	Stage& stage;	
	b2BodyDef body_def;
	b2PolygonShape body_shape;
	b2FixtureDef fixture_def;

	/*virtual b2BodyDef* create_body_def() override;
	virtual b2FixtureDef* create_fixture_def() override;	*/
	Movable(Stage& stage
		, const int x
		, const int y
		, const int angle_rad
		, const int longitude
		, const int height
		, const float restitution);

	virtual void delete_myself() override;
	virtual std::string get_type() = 0;
	virtual void start_contacting(Ubicable* ubicable) override;
	virtual b2Vec2 get_position() override;

	virtual void colision(Movable& movable_obj) override;
	virtual void colision(Static& static_obj) override;
	//void colision(Floor& floor);
};

#endif
