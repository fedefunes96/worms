#ifndef SENSOR_H
#define SENSOR_H

#include <Box2D/Box2D.h>
#include "ubicable.h"

class Sensor : public Ubicable {
private:
	int object_count;

public:
	Sensor();

	void add_at_position(b2Body* body, b2Vec2 pos, float longitude, float height);

	int get_number_colisions();

	virtual std::string get_type() override;
	virtual int get_id() override;
	virtual void create_myself(b2World& world) override;	
	virtual void delete_myself(b2World& world) override;
	virtual void start_contacting() override;
	virtual void stop_contacting(Ubicable* ubicable) override;
	virtual void stop_contacting(Worm* worm) override;
	virtual b2Body* get_body() override;
	virtual bool im_dead() override;
	virtual void force_death() override;

	virtual bool should_collide_with(Ubicable* ubicable) override;
	
	virtual bool should_collide_with(Girder* girder) override;
	virtual bool should_collide_with(Worm* worm) override;
	virtual bool should_collide_with(Throwable* throwable) override;
}; 

#endif
