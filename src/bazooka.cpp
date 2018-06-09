#include "bazooka.h"
#include "usable.h"
#include <Box2D/Box2D.h>
#include "bazooka_missile.h"
#include "worm.h"

Bazooka::Bazooka(Stage& stage
	, const int ammo
	, const float velocity
	, const float angular_velocity
	, const float radius
	, const float restitution
	, const float max_dmg) 
	: Usable(stage, ammo) 
	, velocity(velocity)
	, angular_velocity(angular_velocity)
	, radius(radius)
	, restitution(restitution)
	, max_dmg(max_dmg) {}


/*void Bazooka::action(const float longitude
	, const float height
	, const b2Vec2& from_pos
	, const b2Vec2& dest_pos
	, const std::vector<float>& params) {

	b2Vec2 normalized_dest = dest_pos - from_pos;

	float32 angle = atan2(normalized_dest.y, normalized_dest.x);
*/
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

/*	b2Vec2 where(from_pos.x + 2*longitude*cos(angle), from_pos.y + 2*height*sin(angle));
	b2Vec2 vec_velocity(this->velocity * cos(angle), this->velocity * sin(angle));

	BazookaMissile* missile = new BazookaMissile(this->stage
												, where.x
												, where.y
												, angle
												, vec_velocity
												, this->angular_velocity
												, this->radius
												, this->restitution
												, this->max_dmg);

	this->stage.insert(std::move(std::shared_ptr<Movable>(missile)));
}*/

void Bazooka::action(Worm* worm
	, const b2Vec2& dest_pos
	, const std::vector<int>& params) {

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
	printf("Vel %0.1f %d\n", this->velocity, params[1]);
	float velocity_f = this->velocity * (float(params[1])/100.0);
	printf("VelF %0.1f\n", velocity_f);
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
												, this->angular_velocity
												, this->radius
												, this->restitution
												, this->max_dmg);

	this->stage.insert(std::move(std::shared_ptr<Movable>(missile)));
}

int Bazooka::get_id() {
	return BAZOOKA_ID;
}
