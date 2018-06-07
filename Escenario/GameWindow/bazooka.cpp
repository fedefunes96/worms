#include "bazooka.h"
#include <QDebug>
Bazooka::Bazooka()
{
    this->setIdObj(0);
}

void Bazooka::fire(QGraphicsScene *scene, int angle, int x, int y)
{
    if(this->ammo<=0){ //check por si acaso...
        return;
    }



    qDebug()<<"lanzar misil!!!";
    this->ammo--;
    this->misil = new MisilBazooka();
    scene->addItem(this->misil);
    this->misil->moveTo(angle,x,y);
}
