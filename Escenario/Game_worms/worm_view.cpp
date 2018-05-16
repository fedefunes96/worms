#include "worm_view.h"
#include <QKeyEvent>
#include <QMutex>
#include <QDebug>


void Worm_View::pause() {
    int remaining = timer->remainingTime();
    timer->stop();
    timer->setInterval(remaining);
}

void Worm_View::resume() {
    timer->start();
}

Worm_View::Worm_View(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    moving=false;


    currentFrame = 0;
    spriteImage = new QPixmap(":/image/wormwait.png"); // Load the sprite image QPixmap

    timer = new QTimer();   // Create a timer for sprite animation
    timer->start(30);   // Run the sprite on the signal generation with a frequency of 25 ms


}



void Worm_View::nextFrame_L()
{
    if(!moving){
        return;
    }
    currentFrame += 60;
    if (currentFrame >= spriteImage->height() ){
        currentFrame = 0;
        setPos(x()-1,y());
        this->update(0,0,60,60);
        moving=false;
        return;
    }
    setPos(x()-1,y());
    this->update(0,0,60,60);
}

void Worm_View::nextFrame_R()
{
    if(!moving){
        return;
    }
    currentFrame += 60;
    if (currentFrame >= spriteImage->height() ){
        currentFrame = 0;
        setPos(x()+1,y());
        this->update(0,0,60,60);
        moving=false;
        return;
    }
    setPos(x()+1,y());
    this->update(0,0,60,60);
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
    painter->drawPixmap(0,0, *spriteImage, 0, currentFrame, 60,60);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Worm_View::boundingRect() const
{
    return QRectF(0,0,60,60);
}



void Worm_View::move_Left()
{
    moving=true;
    currentFrame = 0;
    spriteImage = new QPixmap(":/image/wwalk_left.png"); // Load the sprite image QPixmap

    timer->disconnect();
    connect(timer, &QTimer::timeout, this, &Worm_View::nextFrame_L);


}

void Worm_View::move_Right()
{
    moving=true;
    currentFrame = 0;
    spriteImage = new QPixmap(":/image/wwalk_right.png"); // Load the sprite image QPixmap

    timer->disconnect();
    connect(timer, &QTimer::timeout, this, &Worm_View::nextFrame_R);

}

bool Worm_View::is_moving()
{
    return this->moving;
}

void Worm_View::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Left){
        if(!is_moving()){
            move_Left();
        }
    }

    if(event->key() == Qt::Key_Right){
        if(!is_moving()){
            move_Right();
        }
    }
}



