#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QList>
#include <QScrollBar>
#include "movable.h"
#include <stack>
#include "weapons_and_tools.h"
#include "player.h"
#include <QMouseEvent>

class Camera : public QGraphicsView
{
public:
    Camera(QWidget *parent = 0 );
    void addItemToFollow(MovableItem *item);
    void setPlayerActive(Player* player);
    void mousePressEvent(QMouseEvent *event);
    void addScene(QGraphicsScene *scene);
protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void followObject();
private:
    QTimer* timer;
    QGraphicsItem* item;
    std::stack<MovableItem*> itemsToFollow;
    Player* playerActive;

};

#endif // CAMERA_H
