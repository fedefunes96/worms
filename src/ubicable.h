#ifndef UBICABLE_H
#define UBICABLE_H

#include <Box2D/Box2D.h>
#include <string>
//#include "stage.h"
//#include "movable.h"
//#include "static.h"

//class Movable;
//class Static;
class Girder;
class Worm;
class Throwable;

class Ubicable {
public:
	//Ubicable(Stage& stage);
	virtual ~Ubicable() {}
	//virtual void start_contacting(Ubicable* ubicable) = 0;
	virtual void start_contacting(b2Contact* contact) = 0;
	virtual void stop_contacting(Ubicable* ubicable) = 0;
	virtual void stop_contacting(Worm* worm) = 0;
	virtual void create_myself(b2World& world) = 0;
	virtual void delete_myself(b2World& world) = 0;

	virtual bool should_collide_with(Ubicable* ubicable) = 0;

	virtual bool should_collide_with(Girder* girder) = 0;
	virtual bool should_collide_with(Worm* worm) = 0;
	virtual bool should_collide_with(Throwable* throwable) = 0;

	virtual void pre_solve_contact(b2Contact* contact, const b2Manifold* oldManifold) = 0;
	/*virtual void colision(Static& static_obj) = 0;	
	virtual void colision(Girder& girder) = 0;
	virtual void colision(Worm& worm) = 0;	
	virtual void colision(Throwable& throwable) = 0;*/

	virtual b2Body* get_body() = 0;
	virtual void force_death() = 0;
	virtual bool im_dead() = 0;
	virtual std::string get_type() = 0;
	virtual int get_id() = 0;
};

#endif
