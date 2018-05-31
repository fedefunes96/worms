#include "editor_viga_view.h"

editor_viga_view::editor_viga_view(QObject* parent):
     QObject(parent), QGraphicsItem()
{
    currentFrame = 0;
    spriteImage = new QPixmap("../imagenes/viga.png"); // Load the sprite image QPixmap
}

void editor_viga_view::esGrande(bool si)
{
    this->grande = si;
}

void editor_viga_view::rotar()
{

}

bool editor_viga_view::tam()
{
    return this->grande;
}


void editor_viga_view::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* In the graphic renderer we draw the sprite
     * The first two arguments - is the X and Y coordinates of where to put QPixmap
     * The third argument - a pointer to QPixmap
     * 4 and 5 of the arguments - The coordinates in the image QPixmap, where the image is displayed
     * By setting the X coordinate with the variable currentFrame we would like to move the camera on the sprite
     * and the last two arguments - the width and height of the displayed area, that is, the frame
     * */
    if (grande){
        painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 140,50);
    } else {
        painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 70,50);
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF editor_viga_view::boundingRect() const
{
    if (grande){
        return QRectF(0,0,300,50);
    } else {
        return QRectF(0,0,150,50);
    }
}

