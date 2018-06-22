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
    Q_OBJECT
public:
    Camera(QWidget *parent = 0 );
    void addItemToFollow(MovableItem *item);
    void setPlayerActive(Player* player);
    void mousePressEvent(QMouseEvent *event);
    void addScene(QGraphicsScene *scene);
    void delItemToFollow(MovableItem *item);
    bool containsitemToFollow(MovableItem *item);
    void addProjectileToFollow(MovableItem *item);
    void moveRightCam();
    void moveLeftCam();
    void moveUpCam();
    void moveDownCam();
    void setFreeMove(bool val);
    void followObject();
signals:
    void mouseClick();
protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    //void followObject();
private:
    QTimer* timer;
    QGraphicsItem* item;
    std::stack<MovableItem*> itemsToFollow;
    std::stack<MovableItem*> projectileToFollow;
    std::vector<MovableItem*> vectorItems;
    Player* playerActive;
    bool freeMove;

};

#endif // CAMERA_H
