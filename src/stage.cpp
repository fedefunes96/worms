#include "stage.h"
#include <Box2D/Box2D.h>
#include <thread>

Stage::Stage(const float32 time_step, const int32 velocity_iterations
, const int32 position_iterations)
 : time_step(time_step), velocity_iterations(velocity_iterations), 
 position_iterations(position_iterations), gravity(0.0f, -10.0f)
, world(this->gravity, true) {

	t_world = std::thread(&Stage::draw, this);
	game_over = false;
	//t_world.join();
}

void Stage::draw() {
	while(!this->game_over) {
		this->world.Step(
			this->time_step
			, this->velocity_iterations
			, this->position_iterations);

 		for ( b2Body* b = this->world.GetBodyList(); b; b = b->GetNext()) {
 			b2Vec2 pos = b->GetPosition();
 			printf("X: %.02f - Y: %0.2f\n", pos.x, pos.y);
  		}		
	}
}

b2World& Stage::get_world() {
	return this->world;
}

Stage::Stage(Stage&& other)
 : time_step(other.time_step)
 , velocity_iterations(other.velocity_iterations)
 , position_iterations(other.position_iterations) 
 , gravity(other.gravity) 
 , world(std::move(other.world))
 , t_world(std::move(other.t_world)) {
 	this->game_over = other.game_over;
}
/*b2Body* Stage::insert(Ubicable& ubicable) {
	printf("Inserto ubicable\n");

	b2Body* body = world.CreateBody(body_def);

	body->CreateFixture(fixture_def);

	return body;	
}*/

Stage::~Stage() {
	this->game_over=true;
	t_world.join();
}