#ifndef MOVABLE_H
#define MOVABLE_H

#include <Box2D/Box2D.h>
#include <string>
#include "ubicable.h"

class Girder;
class Worm;
class Throwable;
class Stage;

class Movable : public Ubicable {
public:
	virtual ~Movable() {}
	//virtual void start_contacting(Ubicable* ubicable) = 0;
	virtual void start_contacting() = 0;
	virtual void stop_contacting() = 0;
	virtual void delete_myself() = 0;

	/*virtual void colision(Girder& girder) = 0;
	virtual void colision(Worm& worm) = 0;	
	virtual void colision(Throwable& throwable) = 0;*/

	virtual std::string get_type() = 0;
	virtual int get_id() = 0;

	virtual void move_step() = 0;
};

#endif
