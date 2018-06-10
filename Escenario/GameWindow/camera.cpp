#include "camera.h"
#include <QDebug>

Camera::Camera(QWidget *parent):QGraphicsView(parent)
{
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    timer = new QTimer();
    timer->start(1);
    this->playerActive = nullptr;
}


void Camera::addScene(QGraphicsScene *scene)
{
    setScene(scene);
    connect(timer, &QTimer::timeout, this, &Camera::followObject);
}

void Camera::resizeEvent(QResizeEvent *event)
{
    qDebug() << event->size();
    QGraphicsView::resizeEvent(event);
    horizontalScrollBar()->setValue(500);
    verticalScrollBar()->setValue(this->scene()->height());
}





void Camera::mousePressEvent(QMouseEvent *event)
{
    if(this->playerActive->isActive()){
        Worm_View* worm = this->playerActive->getWormActive();
        worm->setClickDir(event->x()+horizontalScrollBar()->value(),
                          this->scene()->height()-(event->y()+verticalScrollBar()->value()));
        emit mouseClick();
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


    if(item->x() > horizontalScrollBar()->value()+200 && item->x()>horizontalScrollBar()->value()+this->width()-200){
        horizontalScrollBar()->setValue( horizontalScrollBar()->value() + 5 );
    }else if(item->x() < horizontalScrollBar()->value()+200){
        horizontalScrollBar()->setValue( horizontalScrollBar()->value() - 5 );
    }


    if(item->y() > verticalScrollBar()->value()+200 && item->y()>verticalScrollBar()->value()+this->height()-200){
        verticalScrollBar()->setValue( verticalScrollBar()->value() + 5 );
    }else if(item->y() < verticalScrollBar()->value()+200){
        verticalScrollBar()->setValue( verticalScrollBar()->value() - 5 );
    }

}

void Camera::setPlayerActive(Player *player)
{
    this->playerActive = player;
}

void Camera::addItemToFollow(MovableItem *item)
{
    this->itemsToFollow.push(item);
}




