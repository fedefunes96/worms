#ifndef CAMERA_H
#define CAMERA_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QList>
#include <QScrollBar>
#include "mybutton.h"
#include "dialogchooseweapon.h"

class Camera : public QGraphicsView
{
public:
    Camera(QGraphicsScene* scene);
    void addItemToFollow(QGraphicsItem *item);
signals:
public slots:

private slots:
    void followObject();
    void handleButton();
private:
    QTimer* timer;
    QGraphicsItem* item;
    int posXcamera_L;
    int posXcamera_R;
    int posYcamera_U;
    int posYcamera_D;
    MyButton* boton;
    DialogChooseWeapon* menuWeapon;

};

#endif // CAMERA_H
