#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include "ubicable.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

class ContactListener : public b2ContactListener {
public:
	void BeginContact(b2Contact* contact) {
		Ubicable* fixt_a = (Ubicable*) contact->GetFixtureA()->GetUserData();
		Ubicable* fixt_b = (Ubicable*) contact->GetFixtureB()->GetUserData();

		//fixt_a->start_contacting(fixt_b);
		//fixt_b->start_contacting(fixt_a);
		fixt_a->start_contacting(contact);
		fixt_b->start_contacting(contact);

		/*if (fixt_a->get_type().compare("Worm") == 0) {
			b2WorldManifold worldManifold;
			contact->GetWorldManifold(&worldManifold);

			printf("X: %0.1f Y: %0.1f\n", worldManifold.normal.x, worldManifold.normal.y);
		} else if (fixt_b->get_type().compare("Worm") == 0) {
			b2WorldManifold worldManifold;
			contact->GetWorldManifold(&worldManifold);

			printf("X: %0.1f Y: %0.1f\n", worldManifold.normal.x, worldManifold.normal.y);
		}*/
	}

	void EndContact(b2Contact* contact) {
		Ubicable* fixt_a = (Ubicable*) contact->GetFixtureA()->GetUserData();
		Ubicable* fixt_b = (Ubicable*) contact->GetFixtureB()->GetUserData();

		fixt_a->stop_contacting(contact);
		fixt_b->stop_contacting(contact);
	}

	/*void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
		Ubicable* fixt_a = (Ubicable*) contact->GetFixtureA()->GetUserData();
		Ubicable* fixt_b = (Ubicable*) contact->GetFixtureB()->GetUserData();

		//fixt_a->pre_solve_contact(fixt_b, oldManifold);
		//fixt_b->pre_solve_contact(fixt_a, oldManifold);
		fixt_a->pre_solve_contact(contact, oldManifold);
		fixt_b->pre_solve_contact(contact, oldManifold);

		float32 desiredSlopeAngle = 45.0;
		b2Vec2 a = b2Mul(b2Mat22((desiredSlopeAngle - 90.0) * (b2_pi / 180.0)), b2Vec2(0.0, 1.0));
		b2Vec2 b = b2Vec2(-a.x, a.y);

		b2WorldManifold worldManifold;
		contact->GetWorldManifold(&worldManifold);

		bool slide = (b2Dot(a, worldManifold.normal) < 0.0) || (b2Dot(b,  worldManifold.normal) < 0.0);

		Ubicable* fixt_a = (Ubicable*) contact->GetFixtureA()->GetUserData();
		Ubicable* fixt_b = (Ubicable*) contact->GetFixtureB()->GetUserData();

		if (fixt_a->get_type().compare("Worm")==0 && slide) {
			((Worm*) fixt_a)->set_slide(true);
			printf("Angle more than 45°\n");
		} else if (fixt_b->get_type().compare("Worm")==0 && slide) {
			((Worm*) fixt_b)->set_slide(true);
			printf("Angle more than 45°\n");
		} 
	}*/
};

#endif
