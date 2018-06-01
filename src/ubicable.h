#ifndef UBICABLE_H
#define UBICABLE_H

#include <Box2D/Box2D.h>
#include <string>
//#include "stage.h"
//#include "movable.h"
//#include "static.h"

//class Movable;
//class Static;
/*class Girder;
class Worm;
class Throwable;
class Stage;*/

class Ubicable {
public:
	//Ubicable(Stage& stage);
	virtual ~Ubicable() {}
	//virtual void start_contacting(Ubicable* ubicable) = 0;
	virtual void start_contacting() = 0;
	virtual void stop_contacting() = 0;
	virtual void create_myself(b2World& world) = 0;
	virtual void delete_myself(b2World& world) = 0;

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
