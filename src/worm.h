#ifndef WORM_H
#define WORM_H

#include <vector>
#include <utility>
#include "usable.h"
#include "movable.h"
#include <Box2D/Box2D.h>
#include "stage.h"
#include <string>
#include "sensor.h"

#define WORM_TYPE "Worm"

enum class MoveDirection : char {
	NONE = 0,
	RIGHT,
	LEFT,
	JUMP_FORW,
	JUMP_BACK
};

class Worm : public Movable {
private:
	Stage& stage;
	static int id_worms;
    const int id_obj;

	b2Body* body;
	//b2Fixture* fixture;
	Sensor sensor_for_jump;

	const int x;
	const int y;
	const int angle_rad;
	const float restitution;
	const int total_health; //Useful for percentage calculations of hp
	const float mov_speed;
	const std::pair<float, float> forw_jump_speed;
	const std::pair<float, float> back_jump_speed;
	const float height_dmg;
	const int longitude;
	const int height;
	int actual_health;
	int owner;
	bool dead;

	MoveDirection facing_direction;
	MoveDirection move_direction;
	b2Vec2 actual_velocity;

	bool is_on_ground();
public:
	Worm(Stage& stage
		, const int x
		, const int y
		, const float angle_rad
		, const int longitude
		, const int height
		, const float restitution
		, const int health
		, const float mov_speed
		, const std::pair<float, float> forw_jump_speed
		, const std::pair<float, float> back_jump_speed
		, const float height_dmg);

	virtual std::string get_type() override;
	virtual int get_id() override;
	virtual void create_myself(b2World& world) override;
	virtual void delete_myself(b2World& world) override;
	//virtual void start_contacting(Ubicable* ubicable) override;
	virtual void start_contacting() override;
	virtual void stop_contacting() override;

	/*virtual void colision(Girder& girder) override;
	virtual void colision(Worm& worm) override;	
	virtual void colision(Throwable& throwable) override;*/

	virtual void move_step(float32 time_step) override;
	virtual b2Body* get_body() override;
	virtual bool im_dead() override;
	virtual void force_death() override;

	int get_health();
	void add_health(int health);

	void receive_dmg(int damage);

	void start_moving(MoveDirection mdirect);

	void use(std::unique_ptr<Usable>& usable, const b2Vec2& dest, const std::vector<float>& params);	
};

#endif
