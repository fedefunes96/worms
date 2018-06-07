#ifndef WEAPON_H
#define WEAPON_H

#include <QGraphicsScene>

class Weapon
{
public:
    Weapon();
    void setIdObj(int type);
    int getIdObj();
    void setAmmo(int ammo);
    int getAmmo();
    virtual void fire(QGraphicsScene *scene,int angle,int x, int y)=0;
protected:
    int idObj;
    int ammo;
    //faltarian los 3 path para los sprites --> mejora
};

#endif
