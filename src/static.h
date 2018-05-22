#ifndef STATIC_H
#define STATIC_H

#include "ubicable.h"
#include "movable.h"
#include <string>
//#include "stage.h"

class Stage;

class Static : public Ubicable {
protected:
	b2Body* body;
	b2Fixture* fixture;	
	Stage& stage;		
	b2BodyDef body_def;
	b2PolygonShape body_shape;
	b2FixtureDef fixture_def;

	/*virtual b2BodyDef* create_body_def() override;
	virtual b2FixtureDef* create_fixture_def() override;	*/
	Static(Stage& stage, const int x, const int y, const int angle_rad
	, const int longitude, const int height);

	virtual void delete_myself() override;
	virtual std::string get_type() = 0;
	virtual void start_contacting(Ubicable* ubicable) override;
	virtual b2Vec2 get_position() override;

	virtual void colision(Movable& movable_obj) override;
	virtual void colision(Static& static_obj) override;
};

#endif
