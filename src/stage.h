#ifndef STAGE_H
#define STAGE_H

#include <Box2D/Box2D.h>
#include <thread>

class Stage {
private:
	const float32 time_step;
	const int32 velocity_iterations;
	const int32 position_iterations;

	b2Vec2 gravity;
	b2World world;
	std::thread t_world;

	bool game_over;

	void draw();
public:
	Stage(const float32 time_step
		, const int32 velocity_iterations
		, const int32 position_iterations
		);

	b2World& get_world();

	Stage(Stage&&);

	~Stage();
};

#endif
