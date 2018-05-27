#ifndef THROWABLE_H
#define THROWABLE_H

#include "ubicable.h"
#include "stage.h"
#include <Box2D/Box2D.h>
#include <string>

#define THROWABLE_TYPE "Throwable"

class Throwable : public Ubicable {
private:
	Stage& stage;
	b2Body* body;
	b2Fixture* fixture;

	static int id_throwables;
    const int id_obj;	

	const float max_dmg;

	void explode();
public:
	Throwable(Stage& stage
	, const int x
	, const int y
	, const float angle_rad
	, const b2Vec2& velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg);

	virtual std::string get_type() override;
	virtual int get_id() override;
	virtual void delete_myself() override;
	virtual void start_contacting(Ubicable* ubicable) override;

	virtual void colision(Girder& girder) override;
	virtual void colision(Worm& worm) override;	
	virtual void colision(Throwable& throwable) override;	
};

#endif
