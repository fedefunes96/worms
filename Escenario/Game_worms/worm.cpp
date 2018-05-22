#include "worm.h"


Worm::Worm(QObject *parent) : QObject(parent), QGraphicsItem()
{
    speed = 1;
    id = 0;

    //esto en realidad tendria que estar en el estado?
    currentFrame = 0;
    spriteImage = new QPixmap(":/images/wormwait.png"); // Load the sprite image QPixmap

}

bool Worm::isCollidingToGirder()
{
    return true;
}

void Worm::setWormId(int id)
{
    this->id = id;
}

void Worm::setWormSpeed(int speed)
{
    this->speed = speed;
}





void Worm::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* In the graphic renderer we draw the sprite
     * The first two arguments - is the X and Y coordinates of where to put QPixmap
     * The third argument - a pointer to QPixmap
     * 4 and 5 of the arguments - The coordinates in the image QPixmap, where the image is displayed
     * By setting the X coordinate with the variable currentFrame we would like to move the camera on the sprite
     * and the last two arguments - the width and height of the displayed area, that is, the frame
     * */
    painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 50,43);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Worm::boundingRect() const
{
    return QRectF(0,0,50,43);//tamaño del worm
}

