#include <iostream>
#include "stage.h"
#include "girder.h"
#include <Box2D/Box2D.h>
#include <chrono>
#include <thread>

int main(int argc, char* argv[]) {
	float32 timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	Stage stage(timeStep, velocityIterations, positionIterations);

	Girder girder(stage, 0, 20, 0, 1, 1);

	//b2Vec2 pos = girder.get_position();

	//printf("X: %.02f - Y: %0.2f\n", pos.x, pos.y);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	return 0;
}
