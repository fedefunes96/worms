#ifndef STATIC_H
#define STATIC_H

#include "ubicable.h"
#include "movable.h"
#include "stage.h"

class Static : public Ubicable {
private:
	b2BodyDef body_def;
	b2PolygonShape body_shape;
	b2FixtureDef fixture_def;

	virtual b2BodyDef* create_body_def() override;
	virtual b2FixtureDef* create_fixture_def() override;	
protected:
	Static(Stage& stage, const int x, const int y, const int angle_rad
	, const int longitude, const int height);

	virtual void start_contacting(Ubicable* ubicable) override;

	void colision(Movable& movable_obj);
	void colision(Static& static_obj);
};

#endif
