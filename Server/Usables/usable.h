#ifndef USABLE_H
#define USABLE_H

#include "Box2D/Box2D.h"
#include <vector>
#include "stage.h"

class Worm;

#define INFINITY_AMMO -1
#define TRANSF_POT_VAR(x) (39.0*x/99.0 + 60.0/99.0)

class Usable {
protected:
	Stage& stage;
	int ammo;
public:
	Usable(Stage& stage, const int ammo);
	
	virtual void action(
		Worm* worm
		, const b2Vec2& dest_pos
		, const std::vector<int> params) = 0;

	void use(
		Worm* worm
		, const b2Vec2& dest_pos
		, const std::vector<int> params);	
	virtual int get_id() = 0;
	int get_ammo();
};

#endif
