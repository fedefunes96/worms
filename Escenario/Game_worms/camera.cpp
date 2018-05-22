#include "camera.h"
#include "mybutton.h"
#include <QDebug>
#include "dialogchooseweapon.h"

Camera::Camera(QGraphicsScene *scene):QGraphicsView()
{
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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



    this->boton->setGeometry(512,710,30,30);
    boton->setAttribute(Qt::WA_TranslucentBackground);
    connect(boton,&QPushButton::clicked,this,&Camera::handleButton);
    scene->addWidget(this->boton);


}


void Camera::handleButton(){
    qDebug()<<"presione boton";
    menuWeapon = new DialogChooseWeapon();
    menuWeapon->setModal(true);
    menuWeapon->exec();
}

void Camera::followObject()
{
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
    if(item->y() >= this->posYcamera_D && verticalScrollBar()->value() != 2000){
        qDebug()<<"bajar camara";
        this->posYcamera_D -=1;
        verticalScrollBar()->setValue(verticalScrollBar()->value()+1);
    }
    */
}



void Camera::addItemToFollow(QGraphicsItem* item2)
{
    this->item=item2;
}




