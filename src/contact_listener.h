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

		fixt_a->stop_contacting();
		fixt_b->stop_contacting();
	}
};

#endif
