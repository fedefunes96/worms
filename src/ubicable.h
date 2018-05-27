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
class Stage;

class Ubicable {
public:
	//Ubicable(Stage& stage);
	virtual ~Ubicable() {}
	virtual void start_contacting(Ubicable* ubicable) = 0;
	virtual void delete_myself() = 0;
	//Special cases
	//Each ubicable needs to know what to do
	//when it collides with another object
	//General cases - Dont do anything
	/*virtual void colision(Movable& movable_obj) = 0;
	virtual void colision(Static& static_obj) = 0;*/	
	virtual void colision(Girder& girder) = 0;
	virtual void colision(Worm& worm) = 0;	
	virtual void colision(Throwable& throwable) = 0;

	virtual std::string get_type() = 0;
	virtual int get_id() = 0;
};

#endif
