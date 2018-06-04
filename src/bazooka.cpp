#include "bazooka.h"
#include "usable.h"
#include <Box2D/Box2D.h>
#include "bazooka_missile.h"

Bazooka::Bazooka(Stage& stage, int ammo) : Usable(stage, ammo) {}

void Bazooka::action(const float longitude
	, const float height
	, const b2Vec2& from_pos
	, const b2Vec2& dest_pos
	, const std::vector<float>& params) {

	b2Vec2 normalized_dest = dest_pos - from_pos;

	float32 angle = atan2(normalized_dest.y, normalized_dest.x);

	/*Worms are boxes
	//Height radius and long radius
	         Worm     Projection of     Sum radius so it doesn't
	  					Missile           overlap
	  										________
	        ____  		  ___              /  ____  \
	       |    |   ->   /   \     ->      | |    | |
	       |____|   ->   \___/     ->      | |____| |
	                                       \________/
	*/
	
	b2Vec2 where(from_pos.x + 2*longitude*cos(angle), from_pos.y + 2*height*sin(angle));
	b2Vec2 velocity(10.0 * cos(angle), 10 * sin(angle));


	BazookaMissile* missile = new BazookaMissile(this->stage
												, where.x
												, where.y
												, angle
												, velocity
												, 0.0
												, 1.0
												, 0
												, 50.0);

	this->stage.insert(std::move(std::shared_ptr<Movable>(missile)));
}

int Bazooka::get_id() {
	return BAZOOKA_ID;
}