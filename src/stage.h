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
#include <condition_variable>
//#include "game.h"

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
	Wind wind;

	std::vector<std::unique_ptr<Ubicable>> ubicables;
	std::vector<std::shared_ptr<Movable>> movables;

	std::vector<std::unique_ptr<Ubicable>> to_create;
	std::vector<std::shared_ptr<Movable>> to_create_mov;

	std::mutex ubicable_m;
	std::mutex movable_m;
	std::mutex something_moving_m;

	bool continue_drawing;
	std::condition_variable something_moving;

	void remove_deads();
	void create_objects();
	void create_objects_mov();

	void pre_initialize();
	void nothing_moving();
public:
	Stage(const std::string& stage_file
		, const float32 time_step
		, const int32 velocity_iterations
		, const int32 position_iterations
		, Game& game
		);

	void draw();
	void stop_drawing();	

	void wait_stop_moving();

	void insert(std::unique_ptr<Ubicable> ubicable);
	void insert(std::shared_ptr<Movable> movable);

	b2World& get_world();

	~Stage();
};

#endif
