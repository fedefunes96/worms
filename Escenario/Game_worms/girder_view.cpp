#include "girder_view.h"

#include <QMatrix>
#include <QGraphicsScene>
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
        pixmap = new QPixmap(":images/grdl4.png");
    }else if(large==70)
    {
        pixmap = new QPixmap(":/images/grds4.png");
    }else{
        //lanzar error de que se creo con un parametro invalido...
    }

    setPixmap(pixmap->transformed(rm));

}

void Girder_View::setPosition(int x, int y)
{
    int width = this->boundingRect().width();
    int height = this->boundingRect().height();
    setPos(x-width/2,y-height/2);
}
