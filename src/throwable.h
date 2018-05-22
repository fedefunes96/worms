#ifndef THROWABLE_H
#define THROWABLE_H

#include "movable.h"
#include "stage.h"
#include <Box2D/Box2D.h>
#include <string>

#define THROWABLE_TYPE "Throwable"

class Throwable : public Movable {
private:
	const float max_dmg;

	void explode();
protected:
	virtual void colision(Movable& movable_obj) override;
	virtual void colision(Static& static_obj) override;	
public:
	Throwable(Stage& stage
	, const int x
	, const int y
	, const int angle_rad
	, const b2Vec2& velocity
	, const int longitude
	, const int height
	, const float restitution
	, const float max_dmg);

	virtual std::string get_type() override;
};

#endif
