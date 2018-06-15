#ifndef STAGE_H
#define STAGE_H

#include "contact_listener.h"
#include "contact_filter.h"
#include <Box2D/Box2D.h>
#include <thread>
#include <vector>
#include "ubicable.h"
#include "movable.h"
#include <mutex>
#include "wind.h"
#include "water.h"
#include <condition_variable>
#include "event_queue.h"
//#include "game.h"

#define TIME_STEP_MS 25

class Game;

class Stage {
private:
	const float32 time_step;
	const int32 velocity_iterations;
	const int32 position_iterations;

	b2Vec2 gravity;
	b2World world;

	std::thread t_world;

	ContactListener contact_listener;
	ContactFilter contact_filter;

	Game& game;

	std::vector<EventQueue*>& event_queues;

	Wind wind;
	Water water;

	std::vector<std::unique_ptr<Ubicable>> ubicables;
	std::vector<std::shared_ptr<Movable>> movables;

	std::vector<std::unique_ptr<Ubicable>> to_create;
	std::vector<std::shared_ptr<Movable>> to_create_mov;

	std::mutex ubicable_m;
	std::mutex movable_m;
	std::mutex something_moving_m;

	std::mutex step_m;

	bool continue_drawing;
	std::condition_variable something_moving;

	void remove_deads();
	void create_objects();
	void create_objects_mov();

	void pre_initialize();
	void nothing_moving();

	void step();
public:
	Stage(const std::string& stage_file
		, const float32 time_step
		, const int32 velocity_iterations
		, const int32 position_iterations
		, Game& game
		, std::vector<EventQueue*>& event_queues
		);

	void draw();
	void stop_drawing();	

	void wait_stop_moving();

	void insert(std::unique_ptr<Ubicable> ubicable);
	void insert(std::shared_ptr<Movable> movable);

	void set_position(Ubicable* ubicable, const b2Vec2 pos);

	float get_wind_speed();
	void random_wind();
	void set_wind(const float min, const float max);
	void set_water(const float water_level);

	b2World& get_world();

	~Stage();
};

#endif
