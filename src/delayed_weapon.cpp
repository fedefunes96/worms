#include "delayed_weapon.h"
#include "usable.h"
#include <Box2D/Box2D.h>

DelayedWeapon::DelayedWeapon(int ammo) : Usable(ammo) {}

void DelayedWeapon::action(const b2Vec2& from_pos, const b2Vec2& dest_pos) {

}