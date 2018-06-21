#ifndef WEAPON_H
#define WEAPON_H


enum class idWeapon : uint8_t {
    BAZOOKA = 0,
    MORTAR,
    GREEN_GRENADE,
    RED_GRENADE,
    BANANA,
    HOLY_GRENADE,
    DYNAMITE,
    BASEBALL_BAT,
    AERIAL_ATTACK,
    TELEPORTATION
};

class Weapon
{
public:
    Weapon();
    void setIdObj(int type);
    int getIdObj();
    void setAmmo(int ammo);
    int getAmmo();
    void fire();
protected:
    int idObj;
    int ammo;
    //faltarian los 3 path para los sprites? --> mejora
};

#endif
