#ifndef WEAPON_H
#define WEAPON_H

#include "generalSounds.h"

class Weapon
{
public:
    Weapon();
    ~Weapon();
    void setIdObj(int type);
    int getIdObj();
    void setAmmo(int ammo);
    int getAmmo();
    void fire();
protected:
    int idObj;
    int ammo;
    generalSounds* tele;
    generalSounds* fireSound;
};

#endif
