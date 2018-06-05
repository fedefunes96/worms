#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include "ubicable.h"
#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener {
public:
	void BeginContact(b2Contact* contact) {
		Ubicable* fixt_a = (Ubicable*) contact->GetFixtureA()->GetUserData();
		Ubicable* fixt_b = (Ubicable*) contact->GetFixtureB()->GetUserData();

		//fixt_a->start_contacting(fixt_b);
		//fixt_b->start_contacting(fixt_a);
		fixt_a->start_contacting();
		fixt_b->start_contacting();
	}

	void EndContact(b2Contact* contact) {
		Ubicable* fixt_a = (Ubicable*) contact->GetFixtureA()->GetUserData();
		Ubicable* fixt_b = (Ubicable*) contact->GetFixtureB()->GetUserData();

		fixt_a->stop_contacting(fixt_b);
		fixt_b->stop_contacting(fixt_a);
	}

	/*void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
		float32 desiredSlopeAngle = 45.0;
		b2Vec2 a = b2Mul(b2Rot((desiredSlopeAngle - 90.0) * (PI / 180.0)), b2Vec(0.0, 1.0));
		b2Vec2 b = b2Vec(-a.x, a.y);

		b2WorldManifold worldManifold;
		contact->GetWorldManifold(&worldManifold);

		bool slide = (b2Dot(a, worldManifold.normal) < 0.0) || (b2Dot(b,  worldManifold.normal) < 0.0);
	}*/
};

#endif
