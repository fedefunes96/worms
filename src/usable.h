#ifndef USABLE_H
#define USABLE_H

#include <Box2D/Box2D.h>

#define INFINITY_AMMO -1

class Usable {
protected:
	int ammo;
public:
	Usable(const int ammo);
	virtual void action(const b2Vec2& from_pos, const b2Vec2& dest_pos) = 0;
	void use(const b2Vec2& from_pos, const b2Vec2& dest_pos);
};

#endif
