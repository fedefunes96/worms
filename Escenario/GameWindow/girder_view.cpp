#include "girder_view.h"

#include <QMatrix>
#include <QGraphicsScene>
#include <QDebug>
Girder_View::Girder_View()
{
}


Girder_View::Girder_View(int angle,int large)
{
    setIdObj(1);
    QPixmap *pixmap;
    QMatrix rm;
    rm.translate(0, 0);
    rm.rotate(-angle);

    if(large==140)
    {
        pixmap = new QPixmap(ROOT_PATH"/resources/images/grdl4.png");
    }else if(large==70)
    {
        pixmap = new QPixmap(ROOT_PATH"/resources/images/grds4.png");
    }else{
        //lanzar error de que se creo con un parametro invalido...
    }

    setPixmap(pixmap->transformed(rm));
    //delete(pixmap);

}

void Girder_View::setPosition(int x, int y)
{
    int width = this->boundingRect().width();
    int height = this->boundingRect().height();
    setPos(x-width/2,y-height/2);
    qDebug()<<"coloque viga en X:"<<x-width/2<<"Y:"<<y-height/2;
}

int Girder_View::getX()
{
    return this->x();
}

int Girder_View::getY()
{
    return this->y();
}

QRectF Girder_View::areaRect()
{
    return this->boundingRect();
}
