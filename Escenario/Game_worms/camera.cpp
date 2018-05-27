#include "camera.h"
#include "mybutton.h"
#include <QDebug>
#include "dialogchooseweapon.h"

Camera::Camera(QGraphicsScene *scene):QGraphicsView()
{
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalScrollBar()->setValue(scene->height()); // no hace falta chequear, se mueve hasta el maximo
    qDebug()<<verticalScrollBar()->value();
    horizontalScrollBar()->setValue(0);
    setFixedSize(1024,768);
    show();
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Camera::followObject);
    timer->start(5);
    this->posXcamera_R=800;
    this->posXcamera_L=200;
    this->posYcamera_D=700;
    this->posYcamera_U=100;


    this->boton = new MyButton();

    setWindowTitle("Worms Armaggedon");

    this->boton->setGeometry(512,scene->height()-40,30,30);
    boton->setAttribute(Qt::WA_TranslucentBackground);
    connect(boton,&QPushButton::clicked,this,&Camera::handleButton);
    scene->addWidget(this->boton);


}



void Camera::handleButton(){
    qDebug()<<"presione boton";    
    menuWeapon = new DialogChooseWeapon();
    menuWeapon->setWindowTitle("Weapons & Tools");
    menuWeapon->setModal(true);
    menuWeapon->exec();

}

void Camera::followObject()
{
    //while item alive & moving -> follow

    if(this->itemsToFollow.empty()){
        return;
    }
    MovableItem* item = this->itemsToFollow.top();
    if(!item->isAlive() || !(item->isSelected())){
        this->itemsToFollow.pop();
        return;
    }


    //esta vivo y quiero aun seguirlo..
    if(item->x() >= this->posXcamera_R && horizontalScrollBar()->value()!=2000)
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
/*
    if(item->y() <= this->posYcamera_U && verticalScrollBar()->value() > 0){
        qDebug()<<"subir camara";
        this->posYcamera_U -=1;
        verticalScrollBar()->setValue(verticalScrollBar()->value()-1);
    }

    if(item->y() >= this->posYcamera_D && verticalScrollBar()->value() != 0){
        qDebug()<<"bajar camara";
        this->posYcamera_D +=1;
        verticalScrollBar()->setValue(verticalScrollBar()->value()+1);
    }
*/
}



void Camera::addItemToFollow(MovableItem *item)
{
    this->itemsToFollow.push(item);
}




