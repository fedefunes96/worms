#ifndef THROWABLE_H
#define THROWABLE_H

#include "movable.h"
#include "stage.h"
#include <Box2D/Box2D.h>
#include <string>
#include "worm.h"

class Throwable : public Movable {
protected:
	Stage& stage;
	Worm* owner;
	b2Body* body;
	//b2Fixture* fixture;

	static int id_throwables;
    const int id_obj;	
    const float x;
    const float y;
    const float angle_rad;
    const b2Vec2 velocity;
	const float radius;
	const float restitution;
	const float max_dmg;
	const float max_pushback;
	const float radius_expl;

	bool dead;
	bool stop_collide_owner;

	virtual void explode();
public:
	Throwable(Stage& stage
	, Worm* owner
	, const float x
	, const float y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float radius
	, const float restitution
	, const float max_dmg
	, const float max_pushback
	, const float radius_expl);

	virtual std::string get_type() = 0;
	virtual int get_id() override;
	virtual void create_myself(b2World& world) override;
	virtual void delete_myself(b2World& world) override;
	//virtual void start_contacting(Ubicable* ubicable) override;
	virtual void start_contacting(b2Contact* contact) override;
	virtual void stop_contacting(Ubicable* ubicable) override;
	virtual void stop_contacting(Worm* worm) override;

	virtual bool should_collide_with(Ubicable* ubicable) override;
	
	virtual bool should_collide_with(Girder* girder) override;
	virtual bool should_collide_with(Worm* worm) override;
	virtual bool should_collide_with(Throwable* throwable) override;
	virtual bool should_collide_with(Sensor* sensor) override;
	/*virtual void colision(Girder& girder) override;
	virtual void colision(Worm& worm) override;	
	virtual void colision(Throwable& throwable) override;	*/

	virtual void move_step(float32 time_step) override;
	virtual b2Body* get_body() override;
	virtual bool im_dead() override;
	virtual void force_death() override;
	virtual bool is_affected_by_wind() = 0;
};

#endif
