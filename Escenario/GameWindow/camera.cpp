#include "camera.h"
#include <QDebug>
#include "girder_view.h"

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
    this->freeMove=false;
}

void Camera::resizeEvent(QResizeEvent *event)
{
    qDebug() << event->size();
    QGraphicsView::resizeEvent(event);
    horizontalScrollBar()->setValue(0);
    verticalScrollBar()->setValue(0);
}





void Camera::mousePressEvent(QMouseEvent *event)
{
    QGraphicsItem *item = this->itemAt(event->x(),-(event->y()+verticalScrollBar()->value()));
    Girder_View *girder = dynamic_cast<Girder_View*>(item);
    if(!girder){
        qDebug()<<"no es girder";
    }else{
        qDebug()<<"es girder";
    }

    if(this->playerActive->isActive()){
        int diff =((-verticalScrollBar()->value()) - (this->height()-13-4));

        qDebug()<<"mouse click x:"<<event->x()<<"y:"<<event->y();
        qDebug()<<"scroll minimo y:"<<-this->height()+13+4;
        qDebug()<<"diferencia"<<diff;

        Worm_View* worm = this->playerActive->getWormActive();
        worm->setClickDir(event->x()+horizontalScrollBar()->value(),
                          (this->height()-event->y()+diff));
        qDebug()<<"mouse click x:"<<event->x()<<"y:"<<event->y();
        qDebug()<<"lo que guardo x:"<<event->x()+horizontalScrollBar()->value()<<"y:"<<(this->height()-event->y()+diff);
        emit mouseClick();
    }
}

void Camera::setFreeMove(bool val)
{
    this->freeMove=val;
}

void Camera::followObject()
{

    if(this->freeMove){
        return;
    }

    MovableItem *item;
    if(!this->projectileToFollow.empty()){
        item = this->projectileToFollow.top();
        if( (!item->isSelect()) && (!item->isAlive() || !item->isMoving()) ){
            this->projectileToFollow.pop();
            return;
        }
    }else if(!this->itemsToFollow.empty()) {
        item= this->itemsToFollow.top();
        if((!item->isSelect()) && (!item->isAlive() || !item->isMoving()) ){
            this->itemsToFollow.pop();
            return;
        }
    }else {
        // aca tengo que seguir al worm que este activo...
        return;
    }

    if(item->x() > horizontalScrollBar()->value()+200 && item->x()>horizontalScrollBar()->value()+this->width()-200){
        horizontalScrollBar()->setValue( horizontalScrollBar()->value() + 9 );
    }else if(item->x() < horizontalScrollBar()->value()+200){
        horizontalScrollBar()->setValue( horizontalScrollBar()->value() - 9 );
    }


    if(item->y() > verticalScrollBar()->value()+200 && item->y()>verticalScrollBar()->value()+this->height()-200){
        verticalScrollBar()->setValue( verticalScrollBar()->value() + 9 );
    }else if(item->y() < verticalScrollBar()->value()+200){
        verticalScrollBar()->setValue( verticalScrollBar()->value() - 9 );
    }

}

void Camera::moveRightCam()
{
    this->freeMove=true;
    horizontalScrollBar()->setValue( horizontalScrollBar()->value() + 15 );
}

void Camera::moveLeftCam()
{
    this->freeMove=true;
    horizontalScrollBar()->setValue( horizontalScrollBar()->value() - 15 );
}

void Camera::moveUpCam()
{
    this->freeMove=true;
    verticalScrollBar()->setValue( verticalScrollBar()->value() - 15 );
    qDebug()<<"valor hscrrol:"<<horizontalScrollBar()->value()<<"vscroll:"<<verticalScrollBar()->value();
}

void Camera::moveDownCam()
{
    this->freeMove=true;
    verticalScrollBar()->setValue( verticalScrollBar()->value() + 15 );
    qDebug()<<"valor hscrrol:"<<horizontalScrollBar()->value()<<"vscroll:"<<verticalScrollBar()->value();
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
