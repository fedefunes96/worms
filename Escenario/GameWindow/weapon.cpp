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
    if(this->idObj==9){ //usar el enum..
        //sonido particular teletrasnportar
        this->tele->play();
    }else{
        //sonido general para armas..
        this->fireSound->play();
    }
    if(this->ammo!=-1){
        this->ammo--;
    }
}


Weapon::Weapon()
{
    this->tele = new generalSounds(ROOT_PATH"/resources/sounds/English/weaponSelect/LAUGH.WAV");
    this->fireSound = new generalSounds(ROOT_PATH"/resources/sounds/English/fire/FIRE.WAV");
}

void Weapon::setIdObj(int type)
{
    this->idObj = type;
}

int Weapon::getIdObj()
{
    return this->idObj;
}
