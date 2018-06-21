#ifndef SENSOR_H
#define SENSOR_H

#include <Box2D/Box2D.h>
#include "ubicable.h"
#include <unordered_map>

class Worm;

class Sensor : public Ubicable {
private:
	Worm& worm;
	int object_count;
	std::unordered_map<int, float> girder_colisions;

public:
	Sensor(Worm& worm);

	void add_at_position(b2Body* body, b2Vec2 pos, float longitude, float height);

	int get_number_colisions();

	virtual std::string get_type() override;
	virtual int get_id() override;
	virtual void create_myself(b2World& world) override;	
	virtual void delete_myself(b2World& world) override;
	virtual void start_contacting(b2Contact* contact) override;
	virtual void stop_contacting(b2Contact* contact) override;
	virtual b2Body* get_body() override;
	virtual bool im_dead() override;
	virtual void force_death() override;

	virtual bool should_collide_with(Ubicable* ubicable) override;
	
	virtual bool should_collide_with(Girder* girder) override;
	virtual bool should_collide_with(Worm* worm) override;
	virtual bool should_collide_with(Throwable* throwable) override;
	virtual bool should_collide_with(Sensor* sensor) override;

	virtual void pre_solve_contact(b2Contact* contact, const b2Manifold* oldManifold) override;
}; 

#endif
