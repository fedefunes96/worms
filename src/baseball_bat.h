#ifndef BASEBALL_BAT_H
#define BASEBALL_BAT_H

#include "usable.h"
#include <Box2D/Box2D.h>
#include "worm.h"

#define BASEBALL_BAT_ID 7

class BaseballBat : public Usable {
private:
	const float velocity;
	const float dmg;

public:
	BaseballBat(Stage& stage
	, const int ammo
	, const float velocity
	, const float dmg);

	virtual void action(
		Worm* worm
		, const b2Vec2& dest_pos
		, const std::vector<int>& params) override;

	virtual int get_id() override;
};

#endif
