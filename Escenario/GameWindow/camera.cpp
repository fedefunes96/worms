#include "camera.h"
#include <QDebug>

Camera::Camera(QWidget *parent):QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Camera::followObject);
    timer->start(1);
    this->posXcamera_R=this->width()-200;
    this->posXcamera_L=200;
    this->posYcamera_D=this->height()-100;
    this->posYcamera_U=100;
    this->playerActive = nullptr;
}


void Camera::addScene(QGraphicsScene *scene)
{
    setScene(scene);
    verticalScrollBar()->setValue(scene->height()); // no hace falta chequear, se mueve hasta el maximo
    horizontalScrollBar()->setValue(0);
}





void Camera::mousePressEvent(QMouseEvent *event)
{
    if(this->playerActive->isActive()){
        //Worm_View* worm = this->playerActive->getWormActive();
        //worm->setDirClick();
    }
}



void Camera::followObject()
{
    //while item alive & moving -> follow

    if(this->itemsToFollow.empty()){
        return;
    }
    MovableItem* item = this->itemsToFollow.top();
    if(!item->isAlive() || !(item->isSelect())){
        this->itemsToFollow.pop();
        return;
    }

    //esta vivo y quiero aun seguirlo..
    if(item->x() >= this->posXcamera_R && horizontalScrollBar()->value()!=this->limitScrollR)
    {
        horizontalScrollBar()->setValue( horizontalScrollBar()->value() + 1 );
        this->posXcamera_R += 1;
    }

    if(item->x() <= this->posXcamera_L && horizontalScrollBar()->value()>0)
    {
        qDebug()<<this->posXcamera_L;
        qDebug()<<horizontalScrollBar()->value();
        horizontalScrollBar()->setValue( horizontalScrollBar()->value() - 1 );
        this->posXcamera_L -= 1;
    }
    //subir y bajar camara

    //qDebug()<<verticalScrollBar()->value();
    //8977
    //qDebug()<<item->y();
    //7775 y subiendo
    if(item->y() <= this->posYcamera_U && verticalScrollBar()->value() > 0){
        qDebug()<<"subir camara";
        this->posYcamera_U -=1;
        verticalScrollBar()->setValue(verticalScrollBar()->value()-1);
    }
/*
    if(item->y() >= this->posYcamera_D && verticalScrollBar()->value() != 0){
        qDebug()<<"bajar camara";
        this->posYcamera_D +=1;
        verticalScrollBar()->setValue(verticalScrollBar()->value()+1);
    }
*/
}

void Camera::setPlayerActive(Player *player)
{
    this->playerActive = player;
}

void Camera::addItemToFollow(MovableItem *item)
{
    this->itemsToFollow.push(item);
}




