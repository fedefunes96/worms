#include "bazooka.h"
#include <QDebug>
Bazooka::Bazooka()
{
    this->setIdObj(0);
}

void Bazooka::fire()
{
    qDebug()<<"lanzar misil!!!";
    this->ammo--;
    //this->misil = new MisilBazooka();
    //scene->addItem(this->misil);
    //this->misil->moveTo(angle,x,y);
}
