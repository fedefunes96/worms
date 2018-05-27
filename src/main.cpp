#include <iostream>
#include "stage.h"
//#include "movable.h"
//#include "static.h"
#include "girder.h"
#include "throwable.h"
#include <Box2D/Box2D.h>
#include <chrono>
#include <thread>
#include "contact_listener.h"
#include "game.h"

int main(int argc, char* argv[]) {
	float32 timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	std::vector<Player> players;

	Game game("hi", std::move(players));

	Stage stage(timeStep, velocityIterations, positionIterations, game);

	b2Vec2 velocity(50.0, 10.0);

	Throwable test_mov(stage
		, 5
		, 2
		, 0
		, velocity
		, 30.0
		, 1.0
		, 0.0
		, 75.0);

	Girder test_static(stage
		, 0
		, 10
		, 0
		, 1
		, 1);

	//stage.draw();
	for (int i = 0; i < 50; i++) {
		stage.draw();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	//Girder girder(stage, 0, 20, 0, 1, 1);

	//b2Vec2 pos = girder.get_position();

	//printf("X: %.02f - Y: %0.2f\n", pos.x, pos.y);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	return 0;
}
