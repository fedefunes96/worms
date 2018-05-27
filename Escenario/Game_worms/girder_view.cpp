#include "girder_view.h"

#include <QMatrix>

Girder_View::Girder_View()
{
}

Girder_View::Girder_View(int angle,int large)
{
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

