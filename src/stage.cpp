#include "stage.h"
#include <Box2D/Box2D.h>
#include <thread>
#include "ubicable.h"
#include "movable.h"
#include "game.h"
#include <vector>
#include <algorithm>

Stage::Stage(const std::string& stage_file
	, const float32 time_step
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
	this->something_moving = false;
}

void Stage::remove_deads() {
	std::lock_guard<std::mutex> lock(this->movable_m);

	std::vector<std::shared_ptr<Movable>>::iterator it = this->movables.begin();

	while (it != this->movables.end()) {
		if ((*it)->im_dead()) {
			(*it)->delete_myself(this->world);
			this->game.notify_removal((*it).get());
			it = this->movables.erase(it);
		} else {
			++it;
		}
	}
}

void Stage::insert(std::unique_ptr<Ubicable> ubicable) {
	//Insert it to create
	std::lock_guard<std::mutex> lock(this->ubicable_m);

	this->to_create.push_back(std::move(ubicable));
}

void Stage::insert(std::shared_ptr<Movable> movable) {
	//Insert it to create
	std::lock_guard<std::mutex> lock(this->movable_m);

	this->to_create_mov.push_back(std::move(movable));
}

void Stage::create_objects() {
	std::lock_guard<std::mutex> lock(this->ubicable_m);

	//std::vector<Ubicable*>::iterator it = this->to_create.begin();
	std::vector<std::unique_ptr<Ubicable>>::iterator it = this->to_create.begin();

	while (it != this->to_create.end()) {
		std::unique_ptr<Ubicable> ubicable = std::move(*it);

		ubicable->create_myself(this->world);

		this->ubicables.push_back(std::move(ubicable));

		it = this->to_create.erase(it);
	}	
}

void Stage::create_objects_mov() {
	std::lock_guard<std::mutex> lock(this->movable_m);

	//std::vector<Ubicable*>::iterator it = this->to_create.begin();
	std::vector<std::shared_ptr<Movable>>::iterator it = this->to_create_mov.begin();

	while (it != this->to_create_mov.end()) {
		std::shared_ptr<Movable> movable = std::move(*it);
		movable->create_myself(this->world);
		//printf("Creating movable\n");
		this->movables.push_back(std::move(movable));

		it = this->to_create_mov.erase(it);
	}	
}

void Stage::draw() {
	//Create first to pre initialize
	//static objects
	this->create_objects();
	this->create_objects_mov();
	this->pre_initialize();
	this->continue_drawing = true;

	while(this->continue_drawing) {
		this->create_objects_mov();

		int cant_objects_moving = 0;

 		std::vector<std::shared_ptr<Movable>>::iterator it = this->movables.begin();

 		while (it != this->movables.end()) {
 			b2Body* b = (*it)->get_body(); 			
 			//Only notify movables moving
 			if (!b->IsAwake()) {
 				++it;
 				continue;
 			}

 			b2Vec2 pos = b->GetWorldCenter();
 			float angle = b->GetAngle();

 			//Movable* movable = (Movable*) b->GetUserData();

 			//Touched water
 			//if (pos.y < this->game.get_water_level()) {

 			if ((*it)->get_type().compare("Bazooka") == 0)
 				printf("Movable: Posx %0.1f - Posy %0.1f - angle %0.1f\n", pos.x, pos.y, angle);

 			if (pos.y < 0.0) {
 				(*it)->force_death();
 			}

 			this->game.notify_position((*it).get(), pos.x, pos.y, angle);

 			//if (b->IsAwake())
 			cant_objects_moving++;

 			(*it)->move_step();
 			//movable->move_step();

 			++it;
  		}

  		if (cant_objects_moving > 0)
  			this->something_moving = true;
  		else
  			this->something_moving = false;

  		//Need mutex type (3)
  		//(cant_objects_moving > 0) 
  		//? this->something_moving = true 
  		//: this->something_moving = false;

  		this->remove_deads();

		this->world.Step(
			this->time_step
			, this->velocity_iterations
			, this->position_iterations);	
	}

	printf("End of world draw\n");
}

bool Stage::is_something_moving() {
	//Need mutex type (3)
	return this->something_moving;
}

void Stage::pre_initialize() {
	//Lets notify every player for every object
	//in the world (only static ones)
 	std::vector<std::unique_ptr<Ubicable>>::iterator it = this->ubicables.begin();

 	while (it != this->ubicables.end()) {
 		b2Body* b = (*it)->get_body();

 		b2Vec2 pos = b->GetWorldCenter();
 		float angle = b->GetAngle();

 		this->game.notify_position((*it).get(), pos.x, pos.y, angle);

 		++it;
  	}	

 	std::vector<std::shared_ptr<Movable>>::iterator it_mov = this->movables.begin();

 	while (it_mov != this->movables.end()) {
 		b2Body* b = (*it_mov)->get_body();

 		b2Vec2 pos = b->GetWorldCenter();
 		float angle = b->GetAngle();

 		this->game.notify_position((*it_mov).get(), pos.x, pos.y, angle);

 		++it_mov;
  	}	  	
}

void Stage::stop_drawing() {
	this->continue_drawing = false;
}

b2World& Stage::get_world() {
	return this->world;
}

Stage::~Stage() {
	//this->game_over=true;
	//t_world.join();
}