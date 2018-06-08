#include "camera.h"
#include "mybutton.h"
#include <QDebug>

Camera::Camera(QWidget *parent):QGraphicsView(parent)
{

}

Camera::Camera(QGraphicsScene *scene,int w, int h):QGraphicsView()
{

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalScrollBar()->setValue(scene->height()); // no hace falta chequear, se mueve hasta el maximo
    horizontalScrollBar()->setValue(0);
    setFixedSize(w,h-55); // el 40 es por la barra de arriba en ubuntu...
    show();
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Camera::followObject);
    timer->start(5);
    this->posXcamera_R=w-200;
    this->posXcamera_L=200;
    this->posYcamera_D=h-100;
    this->posYcamera_U=100;


    this->boton = new MyButton();

    setWindowTitle("Worms Armaggedon");

    this->boton->setGeometry((w/2)-15,this->scene()->height()-40,30,30);
    boton->setAttribute(Qt::WA_TranslucentBackground);
    connect(boton,&QPushButton::clicked,this,&Camera::handleButton);
    scene->addWidget(this->boton);
    this->playerActive = nullptr;

    this->limitScrollR = scene->width() - this->width() -2;



}

std::pair<int,int> Camera::getPosButton()
{
    std::pair<int,int> pos;
    pos.first = this->boton->x();
    pos.second = this->height()-45;
    return pos;
}

void Camera::setVisibleButton(bool visible){
    this->boton->setVisible(visible);
}

void Camera::handleButton(){
    if(!this->playerActive->isActive() || menuWeapon!=nullptr){
        return;
    }
    menuWeapon = new Weapons_and_Tools(this,this->playerActive);
    menuWeapon->setModal(true);
    menuWeapon->setAttribute(Qt::WA_DeleteOnClose);
    menuWeapon->exec();
    menuWeapon=nullptr;
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
        QPoint point = boton->pos();
        this->boton->move(point.x()+1,point.y());
    }

    if(item->x() <= this->posXcamera_L && horizontalScrollBar()->value()>0)
    {
        qDebug()<<this->posXcamera_L;
        qDebug()<<horizontalScrollBar()->value();
        horizontalScrollBar()->setValue( horizontalScrollBar()->value() - 1 );
        this->posXcamera_L -= 1;
        QPoint point = boton->pos();
        this->boton->move(point.x()-1,point.y());
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




