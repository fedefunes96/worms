#ifndef DELAYED_WEAPON_H
#define DELAYED_WEAPON_H

#include "usable.h"
#include <Box2D/Box2D.h>

class DelayedWeapon : public Usable {
private:

public:
	DelayedWeapon(int ammo);
	virtual void action(const b2Vec2& from_pos, const b2Vec2& dest_pos) override;
};

#endif
