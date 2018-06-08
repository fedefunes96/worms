#ifndef DYNAMITE_H
#define DYNAMITE_H

#include "usable.h"
#include <Box2D/Box2D.h>
#include "worm.h"

#define DYNAMITE_ID 6

class Dynamite : public Usable {
private:
	const float radius;
	const float restitution;
	const float max_dmg;

public:
	Dynamite(Stage& stage
	, const int ammo
	, const float radius
	, const float restitution
	, const float max_dmg);

	/*virtual void action(
		const float longitude
		, const float height
		, const b2Vec2& from_pos
		, const b2Vec2& dest_pos
		, const std::vector<float>& params) override;*/
	virtual void action(
		Worm* worm
		, const b2Vec2& dest_pos
		, const std::vector<int>& params) override;

	virtual int get_id() override;
};

#endif
