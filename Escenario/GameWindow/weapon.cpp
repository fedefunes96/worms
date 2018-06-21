#include "weapon.h"

void Weapon::setAmmo(int ammo)
{
    this->ammo=ammo;
}

int Weapon::getAmmo()
{
    return this->ammo;
}

void Weapon::fire()
{
    if(this->idObj==static_cast<int>(idWeapon::TELEPORTATION)){
        //sonido particular teletrasnportar
    }else{
        //sonido general para armas..
    }
    this->ammo--;
}


Weapon::Weapon()
{

}

void Weapon::setIdObj(int type)
{
    this->idObj = type;
}

int Weapon::getIdObj()
{
    return this->idObj;
}
