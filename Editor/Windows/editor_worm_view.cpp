#include "editor_worm_view.h"

#include <QKeyEvent>
#include <QMutex>
#include <QDebug>


Worm_View::Worm_View(int id,QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    currentFrame = 0;
    spriteImage = new QPixmap(ROOT_PATH"/resources/images/wormwait.png");
    this->id = id;
}

Worm_View::~Worm_View()
{
    delete spriteImage;
}

void Worm_View::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit wormSelect(id);
}


void Worm_View::paint(QPainter *painter, 
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 60,60);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Worm_View::boundingRect() const
{
    return QRectF(0,0,50,50);
}
