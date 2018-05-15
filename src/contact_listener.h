#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener {
public:
	void BeginContact(b2Contact* contact) {
		Ubicable* body_a = (Ubicable*) contact->getFixtureA->GetUserData();
		Ubicable* body_b = (Ubicable*) contact->getFixtureB->GetUserData();

		body_a.start_contacting(body_b);
		body_b.start_contacting(body_a);
	}
}

#endif
