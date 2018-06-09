#ifndef WEAPON_H
#define WEAPON_H

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
