#include "editor_viga_grande_view.h"

editor_viga_grande_view::editor_viga_grande_view(QObject* parent):
        QObject(parent), QGraphicsItem()
{
    currentFrame = 0;
    spriteImage = new QPixmap("../images/grdl4.png"); // Load the sprite image QPixmap
}

void editor_viga_grande_view::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 144,50);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF editor_viga_grande_view::boundingRect() const
{
   return QRectF(0,0,144,50);
}
