#ifndef BAZOOKA_H
#define BAZOOKA_H
#include "weapon.h"
#include "misilBazooka.h"
#include <QGraphicsScene>

class Bazooka : public Weapon
{
public:
    Bazooka();
    virtual void fire();
private:
    MisilBazooka *misil;
};

#endif // BAZOOKA_H
