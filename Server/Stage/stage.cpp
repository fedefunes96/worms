#include "stage.h"
#include "Box2D/Box2D.h"
#include <thread>
#include "ubicable.h"
#include "contact_listener.h"
#include "contact_filter.h"
#include "movable.h"
#include "game.h"
#include <vector>
#include <algorithm>
#include "wind.h"
#include <condition_variable>
#include "event_queue.h"
#include "event_position.h"
#include "event_remove.h"
#include <iostream>

Stage::Stage(const std::string& stage_file
	, const float32 time_step
	, const int32 velocity_iterations
	, const int32 position_iterations
	, Game& game
	, std::vector<EventQueue*>& event_queues)
	: time_step(time_step)
	, velocity_iterations(velocity_iterations) 
	, position_iterations(position_iterations)
	, gravity(0.0f, 0.0f)
	, world(this->gravity, true)
	, game(game)
	, event_queues(event_queues)
	, wind(0.1, 1.0)
	, water(0.0) {

	this->world.SetContactListener(&this->contact_listener);
	this->world.SetContactFilter(&this->contact_filter);
}

void Stage::remove_deads() {
	std::lock_guard<std::mutex> lock(this->movable_m);

	std::vector<std::shared_ptr<Movable>>::iterator it = this->movables.begin();

	while (it != this->movables.end()) {
		if ((*it)->im_dead()) {
			(*it)->delete_myself(this->world);

			std::shared_ptr<Event> event(new EventRemove((*it)->get_type()
														, (*it)->get_id()));

			for (int i = 0; i < (int) this->event_queues.size(); i++) {
				//Copy share pointers to everyone
				//Destroy the event when all the players
				//process it
				this->event_queues[i]->add_event(event);
			}

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
 			(*it)->move_step(TIME_STEP_MS);
 			
 			wind.apply((*it).get());

 			b2Body* b = (*it)->get_body(); 		

 			 //Apply gravity each time step
 			b->ApplyForce(b->GetMass()*(*it)->get_gravity(), b->GetWorldCenter());
	
			b2Vec2 pos = b->GetWorldCenter();
			b2Vec2& last_pos = (*it)->get_position();
 			//Only notify movables moving
 			if (pos.x == last_pos.x && pos.y == last_pos.y) {
 				++it;
 				continue;
 			}

 			(*it)->set_position(pos);

 			float angle = b->GetAngle();

 			if (pos.y < this->water.get_water_level()) {
 				(*it)->force_death();
 			}

 			std::shared_ptr<Event> event_pos(new EventPosition((*it)->get_type()
														, (*it)->get_id()
 														, pos.x
 														, pos.y
 														, angle));

			for (int i = 0; i < (int) this->event_queues.size(); i++) {
				//Copy share pointers to everyone
				//Destroy the event when all the players
				//process it
				this->event_queues[i]->add_event(event_pos);
			}

 			cant_objects_moving++;

 			++it;
  		}

  		if (cant_objects_moving == 0 && this->no_explosives_in_map())
  			this->nothing_moving();

  		this->remove_deads();

  		this->step();

		std::this_thread::sleep_for(std::chrono::milliseconds(TIME_STEP_MS));
	}

	printf("End of world draw\n");
}

bool Stage::no_explosives_in_map() {
	std::lock_guard<std::mutex> lock(this->movable_m);

	std::vector<std::shared_ptr<Movable>>::iterator it = this->movables.begin();

	while (it != this->movables.end()) {
		if ((*it)->is_explosive())
			return false;
		++it;
	}		

	return true;
}

void Stage::step() {
	std::lock_guard<std::mutex> lock(this->step_m);

	this->world.Step(
		this->time_step
		, this->velocity_iterations
		, this->position_iterations);		
}

void Stage::set_position(Ubicable* ubicable, const b2Vec2 pos) {
	std::lock_guard<std::mutex> lock(this->step_m);

	b2Body* b = ubicable->get_body();
	float32 angle = b->GetAngle();

	ubicable->get_body()->SetTransform(pos, angle);
}

void Stage::nothing_moving() {
	std::unique_lock<std::mutex> mlock(this->something_moving_m);

	this->something_moving.notify_one();	
}

void Stage::wait_stop_moving() {
	std::unique_lock<std::mutex> mlock(this->something_moving_m);
	
	this->something_moving.wait(mlock);
}

void Stage::pre_initialize() {
	//Lets notify every player for every object
	//in the world (only static ones)
 	std::vector<std::unique_ptr<Ubicable>>::iterator it = this->ubicables.begin();

 	while (it != this->ubicables.end()) {
 		b2Body* b = (*it)->get_body();

 		b2Vec2 pos = b->GetWorldCenter();
 		float angle = b->GetAngle();

 		std::cout << (*it)->get_type() << (*it)->get_id() << std::endl;
 		std::shared_ptr<Event> event(new EventPosition((*it)->get_type()
													, (*it)->get_id()
 													, pos.x
 													, pos.y
 													, angle));
		for (int i = 0; i < (int) this->event_queues.size(); i++) {
			//Copy share pointers to everyone
			//Destroy the event when all the players
			//process it
			this->event_queues[i]->add_event(event);
		}

 		++it;
  	}	

 	std::vector<std::shared_ptr<Movable>>::iterator it_mov = this->movables.begin();

 	while (it_mov != this->movables.end()) {
 		b2Body* b = (*it_mov)->get_body();

 		b2Vec2 pos = b->GetWorldCenter();
 		float angle = b->GetAngle();

 		std::shared_ptr<Event> event(new EventPosition((*it_mov)->get_type()
													, (*it_mov)->get_id()
 													, pos.x
 													, pos.y
 													, angle));
		for (int i = 0; i < (int) this->event_queues.size(); i++) {
			//Copy share pointers to everyone
			//Destroy the event when all the players
			//process it
			this->event_queues[i]->add_event(event);
		}
 		++it_mov;
  	}	 	
}

void Stage::stop_drawing() {
	this->continue_drawing = false;
}

b2World& Stage::get_world() {
	return this->world;
}

void Stage::set_wind(const float min, const float max) {
	this->wind.set_wind_limits(min, max);
}

void Stage::set_water(const float water_level) {
	this->water.set_water_level(water_level);
}

float Stage::get_wind_speed() {
	return this->wind.get_wind_speed();
}

void Stage::random_wind() {
	this->wind.change_wind();
}

Stage::~Stage() {}
