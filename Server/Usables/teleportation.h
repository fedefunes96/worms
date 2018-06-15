#ifndef TELEPORTATION_H
#define TELEPORTATION_H

#include "usable.h"
#include <Box2D/Box2D.h>
#include "worm.h"

#define TELEPORTATION_ID 9

class Teleportation : public Usable {
public:
	Teleportation(Stage& stage
	, const int ammo);

	virtual void action(
		Worm* worm
		, const b2Vec2& dest_pos
		, const std::vector<int> params) override;

	virtual int get_id() override;
};

#endif
