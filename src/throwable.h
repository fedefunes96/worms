#ifndef THROWABLE_H
#define THROWABLE_H

#include "movable.h"
#include "stage.h"
#include <Box2D/Box2D.h>
#include <string>

class Throwable : public Movable {
private:
	Stage& stage;
	b2Body* body;
	//b2Fixture* fixture;

	static int id_throwables;
    const int id_obj;	
    const int x;
    const int y;
    const float angle_rad;
    const b2Vec2 velocity;
	const float angular_velocity;
	const float radius;
	const float restitution;
	const float max_dmg;

	bool dead;

	void explode();
public:
	Throwable(Stage& stage
	, const int x
	, const int y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg);

	virtual std::string get_type() = 0;
	virtual int get_id() override;
	virtual void create_myself(b2World& world) override;
	virtual void delete_myself(b2World& world) override;
	//virtual void start_contacting(Ubicable* ubicable) override;
	virtual void start_contacting() override;
	virtual void stop_contacting() override;

	/*virtual void colision(Girder& girder) override;
	virtual void colision(Worm& worm) override;	
	virtual void colision(Throwable& throwable) override;	*/

	virtual void move_step() override;
	virtual b2Body* get_body() override;
	virtual bool im_dead() override;
	virtual void force_death() override;

};

#endif
