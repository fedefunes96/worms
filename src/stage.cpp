#include "stage.h"
#include <Box2D/Box2D.h>
#include <thread>
#include "ubicable.h"
#include "movable.h"
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
	//this->game_over = false;
	this->something_moving = false;
	//Create stage by parameter
}

void Stage::remove(b2Body* body) {
	std::lock_guard<std::mutex> lock(this->remove_m);
	
	this->game.notify_removal((Ubicable*) body->GetUserData());
	this->to_remove.push_back(body);
}

void Stage::remove_deads() {
	std::lock_guard<std::mutex> lock(this->remove_m);

	std::vector<b2Body*>::iterator it = this->to_remove.begin();

	while (it != this->to_remove.end()) {
		this->world.DestroyBody(*it);
		it = this->to_remove.erase(it);
	}
}

/*b2Body* Stage::insert(b2BodyDef* body_def) {
	//Insert object
	//Need mutex type (2)
	return this->world.CreateBody(body_def);
}*/
void Stage::insert(Ubicable* ubicable) {
	std::lock_guard<std::mutex> lock(this->create_m);

	this->to_create.push_back(ubicable);
}

void Stage::create_objects() {
	std::lock_guard<std::mutex> lock(this->create_m);

	std::vector<Ubicable*>::iterator it = this->to_create.begin();

	while (it != this->to_create.end()) {
		(*it)->create_myself(this->world);
		it = this->to_create.erase(it);
	}	
}

void Stage::draw() {
	//Create first to pre initialize
	this->create_objects();
	this->pre_initialize();
	this->continue_drawing = true;

	while(this->continue_drawing) {
		int cant_objects_moving = 0;

 		for ( b2Body* b = this->world.GetBodyList(); b; b = b->GetNext()) {
 			//Only notify movables
 			if (b->GetType() == b2_staticBody)
 				continue;

 			b2Vec2 pos = b->GetWorldCenter();
 			float angle = b->GetAngle();

 			Movable* movable = (Movable*) b->GetUserData();

 			//Touched water
 			//if (pos.y < this->game.get_water_level()) {

 			//printf("Posx %0.1f - Posy %0.1f - angle %0.1f\n", pos.x, pos.y, angle);

 			if (pos.y < 0.0) {
 				//Notifying position if necessary
 				this->game.notify_position(movable, pos.x, pos.y, angle);
 				movable->delete_myself();
 			} else {
 				this->game.notify_position(movable, pos.x, pos.y, angle);	
 				printf("Pos X: %0.1f - Pos Y: %0.1f - Angle: %0.1f\n", pos.x, pos.y, b->GetAngle());
 			}

 			if (b->IsAwake())
 				cant_objects_moving++;

 			movable->move_step();
  		}

  		if (cant_objects_moving > 0)
  			this->something_moving = true;
  		else
  			this->something_moving = false;

  		//Need mutex type (3)
  		/*(cant_objects_moving > 0) 
  		? this->something_moving = true 
  		: this->something_moving = false;*/

  		this->remove_deads();

  		//Need mutex type (2)
		this->world.Step(
			this->time_step
			, this->velocity_iterations
			, this->position_iterations);	

		this->create_objects();
	}
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
 		float angle = b->GetAngle();

 		this->game.notify_position((Ubicable*) b->GetUserData(), pos.x, pos.y, angle);

 		printf("Pos x: %0.2f - Pos y: %0.2f - angle: %0.2f\n", pos.x, pos.y, angle);
  	}
}

void Stage::stop_drawing() {
	//Need mutex type(4)
	this->continue_drawing = false;
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
	//this->game_over=true;
	//t_world.join();
}