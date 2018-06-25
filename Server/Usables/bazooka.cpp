#include "bazooka.h"
#include "usable.h"
#include "Box2D/Box2D.h"
#include "bazooka_missile.h"
#include "worm.h"

Bazooka::Bazooka(Stage& stage
	, const int ammo
	, const float velocity
	, const float radius
	, const float max_dmg
	, const float max_pushback
	, const float radius_expl) 
	: Usable(stage, ammo) 
	, velocity(velocity)
	, radius(radius)
	, max_dmg(max_dmg)
	, max_pushback(max_pushback)
	, radius_expl(radius_expl) {}

void Bazooka::action(Worm* worm
	, const b2Vec2& dest_pos
	, const std::vector<int> params) {

	b2Body* b = worm->get_body();

	b2Vec2 from_pos = b->GetPosition();
	//float longitude = worm->get_longitude();
	//float height = worm->get_height();

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
	//printf("Angle: %0.6f\n", angle);
	//b2Vec2 where(from_pos.x + longitude*cos(angle), from_pos.y + height*sin(angle));
	float velocity_f = this->velocity * TRANSF_POT_VAR(float(params[0]))/100.0;

	b2Vec2 vec_velocity(velocity_f * cos(angle), velocity_f * sin(angle));

	//printf("Where: %0.1f %0.1f\n", where.x, where.y);

	//printf("Final Velocity: %0.1f %0.1f\n", vec_velocity.x, vec_velocity.y);

	//vec_velocity.Set(0.0, 40.0);

	BazookaMissile* missile = new BazookaMissile(this->stage
												, worm
												, from_pos.x
												, from_pos.y
												, angle
												, vec_velocity
												, this->radius
												, this->max_dmg
												, this->max_pushback
												, this->radius_expl);

	this->stage.insert(std::move(std::shared_ptr<Movable>(missile)));
}

int Bazooka::get_id() {
	return BAZOOKA_ID;
}
