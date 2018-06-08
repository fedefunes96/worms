#include "misilBazooka.h"
#include <QDebug>
#include <QGraphicsScene>

MisilBazooka::MisilBazooka():MovableItem()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    currentFrame=0;
    spriteImage = new QPixmap("../../images/misil.png");
    //timer = new QTimer();   // Create a timer for sprite animation

    update(0,0,60,60);
    this->id = 2; // id del misil...
    this->alive=true;
}

void MisilBazooka::nextFameImpact()
{
    currentFrame += 60;
    if(currentFrame >= spriteImage->height())
    {
        qDebug()<<"entre";
        timer->disconnect();
        timer->stop();
        this->alive=false;
        return;
    }
    this->update(0,0,60,60);
}

void MisilBazooka::moveTo(int angle, int posx, int posy)
{
    qDebug()<<"mover misil";
    int width = this->boundingRect().width();
    int height = this->boundingRect().height();
    QGraphicsScene* sc = this->scene();
    setPos(posx-width/2,sc->height()-posy-height/2);
    setTransform(QTransform().translate(30, 30).rotate(angle).translate(-30, -30));
}


bool MisilBazooka::isMovable()
{
    return true;
}

bool MisilBazooka::isAlive()
{
    return this->alive;
}

void MisilBazooka::setPosition(int x, int y)
{
    int width = this->boundingRect().width();
    int height = this->boundingRect().height();
    setPos(x-width/2,y-height/2);
}



void MisilBazooka::explote()
{

    // hacer que el timer sea singleshoot para hacer la animacion de la explosion...
    //timer->start(40);
    //spriteImage = new QPixmap("../../images/shothit.png");
    //setPos(x()-30,y());
    //currentFrame=0;
    //connect(timer, &QTimer::timeout, this, &MisilBazooka::nextFameImpact);
}

void MisilBazooka::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* In the graphic renderer we draw the sprite
     * The first two arguments - is the X and Y coordinates of where to put QPixmap
     * The third argument - a pointer to QPixmap
     * 4 and 5 of the arguments - The coordinates in the image QPixmap, where the image is displayed
     * By setting the X coordinate with the variable currentFrame we would like to move the camera on the sprite
     * and the last two arguments - the width and height of the displayed area, that is, the frame
     * */
    painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 60,60);
    Q_UNUSED(option);
    Q_UNUSED(widget);

}

QRectF MisilBazooka::boundingRect() const
{
   return QRectF(0,0,60,60);
}



void MisilBazooka::fire()
{

    //timer->disconnect();
    //connect(timer, &QTimer::timeout, this, &MisilBazooka::move);
}

void MisilBazooka::setVisibility(bool vis)
{
    this->setVisible(vis);
}

