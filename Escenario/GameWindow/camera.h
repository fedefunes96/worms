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
#include "player.h"

class Camera : public QGraphicsView
{
public:
    Camera(QWidget *parent = 0 );
    Camera(QGraphicsScene* scene, int w, int h);
    void addItemToFollow(MovableItem *item);
    void setVisibleButton(bool visible);
    void setPlayerActive(Player* player);
    std::pair<int, int> getPosButton();
signals:
public slots:
    void handleButton();
private slots:
    void followObject();
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
    Player* playerActive;
    int limitScrollR;
    int limitScrollU;

};

#endif // CAMERA_H
