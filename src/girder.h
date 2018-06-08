#ifndef GIRDER_H
#define GIRDER_H

#include "ubicable.h"
#include "stage.h"
#include <string>

#define GIRDER_TYPE "Girder"

class Girder : public Ubicable {
private:
	Stage& stage;
	b2Body* body;
	//b2Fixture* fixture;	

	static int id_girders;
    const int id_obj;	
    const int x;
    const int y;
    const float angle_rad;
    const float longitude;
    const float height;
public:
	Girder(Stage& stage
		, const int x
		, const int y
		, const float angle_rad
		, const float longitude
		, const float height);

	virtual std::string get_type() override;
	virtual void create_myself(b2World& world) override;
	virtual void delete_myself(b2World& world) override;
	//virtual void start_contacting(Ubicable* ubicable) override;
	virtual void start_contacting() override;
	virtual void stop_contacting(Ubicable* ubicable) override;
	virtual void stop_contacting(Worm* worm) override;

	virtual bool should_collide_with(Ubicable* ubicable) override;
	
	virtual bool should_collide_with(Girder* girder) override;
	virtual bool should_collide_with(Worm* girder) override;
	virtual bool should_collide_with(Throwable* girder) override;

	virtual void pre_solve_contact(b2Contact* contact, const b2Manifold* oldManifold) override {};
	/*virtual void colision(Girder& girder) override;
	virtual void colision(Worm& worm) override;	
	virtual void colision(Throwable& throwable) override;*/
	virtual int get_id() override;
	virtual b2Body* get_body() override;
	virtual bool im_dead() override;
	virtual void force_death() override;

	//Girder(Girder&&);
};

#endif
