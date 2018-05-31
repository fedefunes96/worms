#ifndef BAZOOKA_H
#define BAZOOKA_H

#include "usable.h"
#include <Box2D/Box2D.h>

#define BAZOOKA_ID 1

class Bazooka : public Usable {
public:
	Bazooka(int ammo);
	virtual void action(const b2Vec2& from_pos, const b2Vec2& dest_pos, std::vector<float> params) override;
	virtual int get_id() override;
};

#endif
