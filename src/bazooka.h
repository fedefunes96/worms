#ifndef BAZOOKA_H
#define BAZOOKA_H

#include "usable.h"
#include <Box2D/Box2D.h>

class Bazooka : public Usable {
public:
	Bazooka(int ammo);
	virtual void action(const b2Vec2& from_pos, const b2Vec2& dest_pos) override;
};

#endif
