#include "girder_view.h"

Girder_View::Girder_View()
{
}

Girder_View::Girder_View(int angle,int large)
{
    if(large==140)
    {
        setPixmap(QPixmap(":/images/grdl0.png"));
    }else if(large==70)
    {
        setPixmap(QPixmap(":/images/grds0.png"));
    }else{
        //lanzar error de que se creo con un parametro invalido...
    }

    QGraphicsPixmapItem::setRotation(angle);
}
