#include "editor_viga_grande_view.h"


editor_viga_grande_view::editor_viga_grande_view(int id, QObject* parent):
        QObject(parent), QGraphicsItem()
{
    currentFrame = 0;
    spriteImage = new QPixmap(ROOT_PATH"/resources/images/grdl4.png");
    this->id = id;
}

editor_viga_grande_view::~editor_viga_grande_view()
{
    delete spriteImage;
}

void editor_viga_grande_view::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit this->girderSelect(id);
}

void editor_viga_grande_view::paint(QPainter *painter, 
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 140,19);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF editor_viga_grande_view::boundingRect() const
{
   return QRectF(0,0,140,19);
}
