#ifndef STAGE_H
#define STAGE_H

#include "contact_listener.h"
#include <Box2D/Box2D.h>
#include <thread>
#include <vector>
#include "ubicable.h"
#include <mutex>
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
	Game& game;

	//std::mutex m;

	std::vector<std::unique_ptr<Ubicable>> ubicables;

	std::vector<Ubicable*> to_create;
	std::vector<b2Body*> to_remove;

	std::mutex create_m;
	std::mutex remove_m;

	bool continue_drawing;
	bool something_moving;

	void remove_deads();
	void create_objects();
	void pre_initialize();
public:
	Stage(const float32 time_step
		, const int32 velocity_iterations
		, const int32 position_iterations
		, Game& game
		);

	void draw();
	void stop_drawing();	
	void remove(b2Body* body);
	bool is_something_moving();
	void insert(Ubicable* ubicable);
	//b2Body* insert(b2BodyDef* body_def);

	b2World& get_world();

	//Stage(Stage&&);

	~Stage();
};

#endif
