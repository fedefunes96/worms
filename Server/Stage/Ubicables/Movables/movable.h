#ifndef MOVABLE_H
#define MOVABLE_H

#include <Box2D/Box2D.h>
#include <string>
#include "ubicable.h"

#define DEFAULT_GRAVITY b2Vec2(0.0, -9.8)

class Girder;
class Worm;
class Throwable;
class Stage;

class Movable : public Ubicable {
private:
	//Default real world gravity
	b2Vec2 gravity = DEFAULT_GRAVITY;
	b2Vec2 last_pos;
public:
	//virtual void start_contacting(Ubicable* ubicable) = 0;
	virtual void start_contacting(b2Contact* contact) = 0;
	virtual void stop_contacting(b2Contact* contact) = 0;
	virtual void create_myself(b2World& world) = 0;	
	virtual void delete_myself(b2World& world) = 0;

	virtual void pre_solve_contact(b2Contact* contact, const b2Manifold* oldManifold) override {};

	Movable(float x, float y) {
		this->last_pos = b2Vec2(x, y);
	}

	void set_position(b2Vec2 pos) {
		this->last_pos = pos;
	}

	b2Vec2& get_position() {
		return this->last_pos;
	}

	void set_gravity(const b2Vec2 gravity) {
		this->gravity = gravity;
	}

	b2Vec2& get_gravity() {
		return this->gravity;
	}

	/*virtual void colision(Girder& girder) = 0;
	virtual void colision(Worm& worm) = 0;	
	virtual void colision(Throwable& throwable) = 0;*/

	virtual std::string get_type() = 0;
	virtual int get_id() = 0;

	virtual void force_death() = 0;
	virtual void move_step(float32 time_step) = 0;
	virtual b2Body* get_body() = 0;
	virtual bool im_dead() = 0;
	virtual bool is_affected_by_wind() = 0;
	virtual bool is_explosive() = 0;

	virtual bool should_collide_with(Ubicable* ubicable) = 0;
	
	virtual bool should_collide_with(Girder* girder) = 0;
	virtual bool should_collide_with(Worm* worm) = 0;
	virtual bool should_collide_with(Throwable* throwable) = 0;
	virtual bool should_collide_with(Sensor* sensor) = 0;
};

#endif
