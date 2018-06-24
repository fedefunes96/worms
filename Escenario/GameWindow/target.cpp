#include "target.h"
#include <QGraphicsScene>
#include <QDebug>


Target::Target():QGraphicsItem()
{
    this->spriteImage = new QPixmap(ROOT_PATH"/resources/images/target.png");
    this->currentFrame=0;
}

Target::~Target()
{
    if(this->spriteImage){
        delete(this->spriteImage);
    }
}

void Target::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 150,60);
    Q_UNUSED(option);
    Q_UNUSED(widget);

}

QRectF Target::boundingRect() const
{
    return QRectF(0,0,150,60);
}

void Target::setTarget(int posx, int posy,int angle){
    setPos(posx,posy);
    setTransform(QTransform().translate(30, 30).rotate(angle).translate(-30, -30));
}
