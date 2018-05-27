#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QImage>
#include <string>
#include <QObject>
#include "worm_view.h"
#include "camera.h"

class Game_View
{
private:
    QGraphicsScene* scene;
    Camera* camera;

public:
    Game_View();
    void update_view();
    void add_Item(QGraphicsItem* item,int posx, int posy);
    void del_Item(QGraphicsItem* item);
    void setBackground(std::string& path);
    QGraphicsItem *itemAt(int posx,int posy);
    Camera *getCamera();
    Worm_View *getWormActive();   // esto no se si tiene sentido...

    void centerScreen(QRect rect);
    void maximizateScreen();
    void minimizateScreen();
    void addWidget(QWidget *widget);

    void moveObjTo(int id,int posX, int posY, int angle);
    void addItemToFollow(MovableItem *item);
};

#endif // GAME_VIEW_H
