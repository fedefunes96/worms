#include "camera.h"
#include <QDebug>

Camera::Camera(QWidget *parent):QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Camera::followObject);
    timer->start(1);
    this->playerActive = nullptr;
}


void Camera::addScene(QGraphicsScene *scene)
{
    setScene(scene);
    verticalScrollBar()->setValue(scene->height()); // no hace falta chequear, se mueve hasta el maximo
    horizontalScrollBar()->setValue(0);
    this->limitScrollR=scene->width()-this->width();
    this->limitScrollD=scene->height()-this->height();

    this->posXcamera=0;
    this->posXcamera_R=this->width()-200+this->posXcamera;
    this->posXcamera_L=this->posXcamera+200;

    this->posYcamera=verticalScrollBar()->value();
    this->posYcamera_D=this->width()-200;
    this->posYcamera_U=this->posYcamera+200;
}

void Camera::resizeEvent(QResizeEvent *event)
{
    qDebug() << event->size();
    QGraphicsView::resizeEvent(event);
    this->limitScrollR=this->scene()->width()-this->width();
    this->limitScrollD=this->scene()->height()-this->height();

    this->posXcamera_R=this->width()-200+this->posXcamera;
    this->posXcamera_L=this->posXcamera+200;

    this->posYcamera_D=this->width()-200+this->posYcamera;
    this->posYcamera_U=this->posYcamera+200;

    this->posYcamera_D=0;
    this->posYcamera_U=0;
}





void Camera::mousePressEvent(QMouseEvent *event)
{
    if(this->playerActive->isActive()){
        Worm_View* worm = this->playerActive->getWormActive();
        qDebug()<<"click posX:"<<event->x()<<"posY:"<<event->y();
        worm->setClickDir(event->x(),event->y());
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

    //qDebug()<<"itemX:"<<item->x()<<"itemY:"<<item->y()<<"HB:"<<horizontalScrollBar()->value()<<"VB"<<verticalScrollBar()->value()<<"posXcamera_R:"<<this->posXcamera_R<<"posXcamera_L:"<<this->posXcamera_L<<"posXcamera:"<<this->posXcamera<<"posYcamera_D:"<<this->posYcamera_D<<"posYcamera_U:"<<this->posYcamera_U<<"posYcamera:"<<this->posYcamera;

    //esta vivo y quiero aun seguirlo..
    if(item->x() >= this->posXcamera_R && horizontalScrollBar()->value()!=this->limitScrollR)
    {
        horizontalScrollBar()->setValue( horizontalScrollBar()->value() + 1 );
        this->posXcamera += 1;
        this->posXcamera_R +=1;
        this->posXcamera_L +=1;
    }else if(item->x() <= this->posXcamera_L && horizontalScrollBar()->value()>0)
    {
        horizontalScrollBar()->setValue( horizontalScrollBar()->value() - 1 );
        this->posXcamera -= 1;
        this->posXcamera_L -=1;
        this->posXcamera_R -=1;
    }

    if(item->y() > this->posYcamera_D && verticalScrollBar()->value()<this->limitScrollD)
    {
        verticalScrollBar()->setValue( verticalScrollBar()->value() + 1 );
        this->posYcamera += 1;
        this->posYcamera_D +=1;
        this->posYcamera_U +=1;
    }else if(item->y() < this->posYcamera_U && verticalScrollBar()->value()>0)
    {
        verticalScrollBar()->setValue( verticalScrollBar()->value() + 1 );
        this->posYcamera += 1;
        this->posYcamera_D +=1;
        this->posYcamera_U +=1;
    }




    //subir y bajar camara

    //qDebug()<<verticalScrollBar()->value();
    //8977
    //qDebug()<<item->y();
    //7775 y subiendo
/*
    if(item->y() <= this->posYcamera && verticalScrollBar()->value() > 0){
        qDebug()<<"subir camara";
        this->posYcamera_U -=1;
        verticalScrollBar()->setValue(verticalScrollBar()->value()-1);
    }
*/


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




