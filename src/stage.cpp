#include "stage.h"
#include <Box2D/Box2D.h>
#include <thread>
#include "ubicable.h"
#include "game.h"
#include <vector>

Stage::Stage(const float32 time_step
	, const int32 velocity_iterations
	, const int32 position_iterations
	, Game& game)
	: time_step(time_step)
	, velocity_iterations(velocity_iterations) 
	, position_iterations(position_iterations)
	, gravity(0.0f, -10.0f)
	, world(this->gravity, true)
	, game(game) {

	this->world.SetContactListener(&this->contact_listener);
	this->game_over = false;
	this->something_moving = false;
	//Create stage by parameter

	this->pre_initialize();
}

void Stage::remove(b2Body* body) {
	//Remove object
	//Need mutex type (1)
	this->game.notify_removal((Ubicable*) body->GetUserData());
	this->to_remove.push_back(body);
}

void Stage::remove_deads() {
	//Need mutex type (1)
	std::vector<b2Body*>::iterator it = this->to_remove.begin();

	while (it != this->to_remove.end()) {
		this->world.DestroyBody(*it);
		it = this->to_remove.erase(it);
	}
}

b2Body* Stage::insert(b2BodyDef* body_def) {
	//Insert object
	//Need mutex type (2)
	return this->world.CreateBody(body_def);
}

void Stage::draw() {
	//this->pre_initialize();
	//while(!this->game_over) {

		int cant_objects_moving = 0;

 		for ( b2Body* b = this->world.GetBodyList(); b; b = b->GetNext()) {
 			//Only notify movables
 			if (b->GetType() != b2_dynamicBody)
 				continue;

 			b2Vec2 pos = b->GetWorldCenter();
 			Ubicable* ubic = (Ubicable*) b->GetUserData();

 			//Touched water
 			if (pos.y < 0.0) {
 				//Notifying position if necessary
 				this->game.notify_position((Ubicable*) b->GetUserData(), pos.x, pos.y);
 				ubic->delete_myself();
 			} else {
 				this->game.notify_position((Ubicable*) b->GetUserData(), pos.x, pos.y);	
 			}

 			if(b->IsAwake())
 				cant_objects_moving++;
  		}

  		/*if (cant_objects_moving > 0)
  			this->something_moving = true;
  		else
  			this->something_moving = false;*/

  		//Need mutex type (3)
  		(cant_objects_moving > 0) 
  		? this->something_moving = true 
  		: this->something_moving = false;

  		this->remove_deads();

  		//Need mutex type (2)
		this->world.Step(
			this->time_step
			, this->velocity_iterations
			, this->position_iterations);		
	//}
}

bool Stage::is_something_moving() {
	//Need mutex type (3)
	return this->something_moving;
}

void Stage::pre_initialize() {
	//Lets notify every player for every object
	//in the world (including static ones)
 	for ( b2Body* b = this->world.GetBodyList(); b; b = b->GetNext()) {
 		b2Vec2 pos = b->GetWorldCenter();

 		this->game.notify_position((Ubicable*) b->GetUserData(), pos.x, pos.y);
  	}
}

void Stage::stop_drawing() {
	this->game_over = true;
}

b2World& Stage::get_world() {
	return this->world;
}

/*Stage::Stage(Stage&& other)
 : time_step(other.time_step)
 , velocity_iterations(other.velocity_iterations)
 , position_iterations(other.position_iterations) 
 , gravity(other.gravity) 
 , world(std::move(other.world))
 , t_world(std::move(other.t_world)
 , game(other.game)) {
 	this->game_over = other.game_over;
}*/
/*b2Body* Stage::insert(Ubicable& ubicable) {
	printf("Inserto ubicable\n");

	b2Body* body = world.CreateBody(body_def);

	body->CreateFixture(fixture_def);

	return body;	
}*/

Stage::~Stage() {
	this->game_over=true;
	//t_world.join();
}