#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include "ubicable.h"
#include "Box2D/Box2D.h"
#include "Box2D/Common/b2Math.h"

class ContactListener : public b2ContactListener {
public:
	void BeginContact(b2Contact* contact) {
		Ubicable* fixt_a = (Ubicable*) contact->GetFixtureA()->GetUserData();
		Ubicable* fixt_b = (Ubicable*) contact->GetFixtureB()->GetUserData();

		fixt_a->start_contacting(contact);
		fixt_b->start_contacting(contact);
	}

	void EndContact(b2Contact* contact) {
		Ubicable* fixt_a = (Ubicable*) contact->GetFixtureA()->GetUserData();
		Ubicable* fixt_b = (Ubicable*) contact->GetFixtureB()->GetUserData();

		fixt_a->stop_contacting(contact);
		fixt_b->stop_contacting(contact);
	}
};

#endif
