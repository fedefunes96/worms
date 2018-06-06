#include "teleportation.h"
#include "usable.h"
#include <Box2D/Box2D.h>
#include "worm.h"

Teleportation::Teleportation(Stage& stage
	, const int ammo) 
	: Usable(stage, ammo) {}

void Teleportation::action(Worm* worm
	, const b2Vec2& dest_pos
	, const std::vector<float>& params) {

	/*b2Body* b = worm->get_body();

	b2Vec2 from_pos = b->GetPosition();
	float longitude = worm->get_longitude();
	float height = worm->get_height();

	b2Vec2 normalized_dest = dest_pos - from_pos;

	float32 angle = atan2(normalized_dest.y, normalized_dest.x);

	b2Vec2 where(from_pos.x + 2*longitude*cos(angle), from_pos.y + 2*height*sin(angle));
	b2Vec2 vec_velocity(this->velocity * cos(angle), this->velocity * sin(angle));

	BazookaMissile* missile = new BazookaMissile(this->stage
												, worm
												, where.x
												, where.y
												, angle
												, vec_velocity
												, this->angular_velocity
												, this->radius
												, this->restitution
												, this->max_dmg);

	this->stage.insert(std::move(std::shared_ptr<Movable>(missile)));*/
}

int Teleportation::get_id() {
	return TELEPORTATION_ID;
}
