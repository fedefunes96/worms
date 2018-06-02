#include "bazooka.h"
#include "worm_view.h"
#include <QDebug>

Bazooka::Bazooka(Worm_View* w2):MovableItem()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    w=w2;
    currentFrame=0;
    spriteImage = new QPixmap(":/images/bazooka.1.png");
    timer = new QTimer();   // Create a timer for sprite animation
    timer->start(2);   // Run the sprite on the signal generation with a frequency of 25 ms
    timer2 = new QTimer();   // Create a timer for sprite animation
    timer2->start(2);   // Run the sprite on the signal generation with a frequency of 25 ms
    update(0,0,30,30);
    this->id = 700;
    this->alive=true;
}

void Bazooka::nextFameImpact()
{
    currentFrame += 60;
    if(currentFrame >= spriteImage->height())
    {
        qDebug()<<"entre";
        timer->disconnect();
        timer2->disconnect();
        timer->stop();
        timer2->stop();
        this->alive=false;
        w->delete_bullet(this);
        return;
    }
    this->update(0,0,60,60);
}

void Bazooka::moveTo(int angle, int posx, int posy)
{
    // ver tema de anulos en la trayectoria... rotar imagen como se hizo para la viga
}


bool Bazooka::isMovable()
{
    return true;
}

bool Bazooka::isAlive()
{
    return this->alive;
}

void Bazooka::move()
{
    setPos(x()-1,y());
}

void Bazooka::mover()
{

}

void Bazooka::runSpriteWeapon()
{

}

void Bazooka::setPosition(int x, int y)
{

}

void Bazooka::explote()
{
    timer2->disconnect();
    timer2->stop();
    timer->disconnect();
    timer->stop();
    timer->start(40);
    spriteImage = new QPixmap(":/images/shothit.png");
    setPos(x()-30,y());
    currentFrame=0;
    connect(timer, &QTimer::timeout, this, &Bazooka::nextFameImpact);
}

void Bazooka::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

QRectF Bazooka::boundingRect() const
{
   return QRectF(0,0,60,60);
}

bool Bazooka::colliding()
{
    QList<QGraphicsItem*> list = collidingItems();
    if(list.empty()){
        return false;
    }
    return true;
}

void Bazooka::setAngle(int x, int y)
{
    this->angle.first = x;
    this->angle.second = y;
}

void Bazooka::fire()
{
    timer2-disconnect();
    connect(timer2, &QTimer::timeout, this, &Bazooka::explote);
    timer2->start(500);
    //timer2->singleShot(300);
    timer->disconnect();
    connect(timer, &QTimer::timeout, this, &Bazooka::move);
}



