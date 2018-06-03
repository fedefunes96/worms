#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QList>
#include <QScrollBar>
#include "mybutton.h"
#include "movable.h"
#include <stack>
#include "weapons_and_tools.h"
#include "worm_view.h"

class Camera : public QGraphicsView
{
public:
    Camera(QWidget *parent = 0 );
    Camera(QGraphicsScene* scene, int w, int h);
    void addItemToFollow(MovableItem *item);
    void setVisibleButton(bool visible);
    void setWormActive(Worm_View* worm);
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
    Weapons_and_Tools* menuWeapon;
    std::stack<MovableItem*> itemsToFollow;
    Worm_View* wormActive;

};

#endif // CAMERA_H
