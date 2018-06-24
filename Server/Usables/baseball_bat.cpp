#include "baseball_bat.h"
#include "usable.h"
#include "Box2D/Box2D.h"
#include "worm.h"
#include "query_callback.h"

BaseballBat::BaseballBat(Stage& stage
	, const int ammo
	, const float velocity
	, const float dmg) 
	: Usable(stage, ammo) 
	, velocity(velocity)
	, dmg(dmg) {}


void BaseballBat::action(Worm* worm
	, const b2Vec2& dest_pos
	, const std::vector<int> params) {

	printf("Using BaseballBat\n");

	b2Body* b = worm->get_body();

	b2Vec2 from_pos = b->GetWorldCenter();

	//Query pos and do dmg in Area
	QueryCallback queryCallback;
	b2AABB aabb;

	float longitude = worm->get_longitude();
	float height = worm->get_height();

	switch (worm->get_facing_direction()) {
		case MoveDirection::RIGHT: {
			aabb.lowerBound = from_pos + b2Vec2(0.5*longitude, -height);
			aabb.upperBound = from_pos + b2Vec2(2*longitude, height);
			break;
		}
		case MoveDirection::LEFT: {
			aabb.lowerBound = from_pos - b2Vec2(2*longitude, height);
			aabb.upperBound = from_pos - b2Vec2(0.5*longitude, -height);			
			break;
		}
		default: break;
	}

	this->stage.get_world().QueryAABB(&queryCallback, aabb);

	for (int i = 0; i < (int) queryCallback.foundBodies.size(); i++) {
		b2Body* body = queryCallback.foundBodies[i];
		b2Vec2 bodyCom = body->GetWorldCenter();
	      
		Ubicable* ubicable = (Ubicable*) body->GetUserData();

		if (ubicable->get_type().compare("Worm")==0) {
			if (((Worm*) ubicable)->get_id() == worm->get_id()) {
				//Don't hit myself
				continue;
			}

			//Get angle between the target worm and myself
			b2Vec2 normalized_dest = bodyCom - from_pos;

			float32 angle = atan2(normalized_dest.y, normalized_dest.x);

			b2Vec2 vec_velocity(this->velocity * cos(angle), this->velocity * sin(angle));			

			((Worm*) ubicable)->receive_explosion(vec_velocity);
			((Worm*) ubicable)->receive_dmg(dmg);
		}
	}
}

int BaseballBat::get_id() {
	return BASEBALL_BAT_ID;
}
