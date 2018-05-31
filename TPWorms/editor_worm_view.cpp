#include "editor_worm_view.h"

#include <QKeyEvent>
#include <QMutex>
#include <QDebug>


Worm_View::Worm_View(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    currentFrame = 0;
    spriteImage = new QPixmap("../imagenes/wormwait.png"); // Load the sprite image QPixmap
}

void Worm_View::rotar()
{

}


void Worm_View::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* In the graphic renderer we draw the sprite
     * The first two arguments - is the X and Y coordinates of where to put QPixmap
     * The third argument - a pointer to QPixmap
     * 4 and 5 of the arguments - The coordinates in the image QPixmap, where the image is displayed
     * By setting the X coordinate with the variable currentFrame we would like to move the camera on the sprite
     * and the last two arguments - the width and height of the displayed area, that is, the frame
     * */
    painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 50,50);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Worm_View::boundingRect() const
{
    return QRectF(0,0,50,50);
}
