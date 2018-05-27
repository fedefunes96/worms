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
#include "movable.h"
#include <stack>

class Camera : public QGraphicsView
{
public:
    Camera(QGraphicsScene* scene);
    void addItemToFollow(MovableItem *item);
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
    std::stack<MovableItem*> itemsToFollow;

};

#endif // CAMERA_H
