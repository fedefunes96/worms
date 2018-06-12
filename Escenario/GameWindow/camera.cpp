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



    MovableItem *item;
    if(!this->projectileToFollow.empty()){
        qDebug()<<" saque un proyectil a seguir !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        item = this->projectileToFollow.top();
        if( (!item->isSelect()) && (!item->isAlive() || !item->isMoving()) ){
            this->projectileToFollow.pop();
            return;
        }
    }else{
        if(this->itemsToFollow.empty()){
            return;
        }
        qDebug()<<" w a seguir !!!!!!!!!!!!! ??????????????";
        item= this->itemsToFollow.top();
        if( (!item->isSelect()) && (!item->isAlive() || !item->isMoving()) ){
            this->itemsToFollow.pop();
            return;
        }
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
    this->vectorItems.push_back(item);
}


void Camera::addProjectileToFollow(MovableItem *item){
    this->projectileToFollow.push(item);
    this->vectorItems.push_back(item);
}



void Camera::delItemToFollow(MovableItem *item)
{
    for (unsigned int var = 0; var < this->vectorItems.size(); ++var) {
        if(this->vectorItems[var]->getId()==item->getId() &&
                this->vectorItems[var]->getIdObj()==item->getIdObj()){
            this->vectorItems.erase(this->vectorItems.begin() + var);
            return;
        }
    }
}

bool Camera::containsitemToFollow(MovableItem *item)
{
    for (unsigned int var = 0; var < this->vectorItems.size(); ++var) {
        if(this->vectorItems[var]->getId()==item->getId() &&
                this->vectorItems[var]->getIdObj()==item->getIdObj()){
            return true;
        }
    }
    return false;
}
