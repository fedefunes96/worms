#ifndef CONTACT_FILTER_H
#define CONTACT_FILTER_H

#include "ubicable.h"
#include <Box2D/Box2D.h>

class ContactFilter : public b2ContactFilter {
public:
	bool ShouldCollide(b2Fixture* fixt_a, b2Fixture* fixt_b) {
		Ubicable* ubi_a = (Ubicable*) fixt_a->GetUserData();
		Ubicable* ubi_b = (Ubicable*) fixt_b->GetUserData();

		bool b1 = ubi_a->should_collide_with(ubi_b);
		bool b2 = ubi_b->should_collide_with(ubi_a);

		//Both says that collides
		if (b1 && b2)
			return true;

		return false;
	}
};

#endif
