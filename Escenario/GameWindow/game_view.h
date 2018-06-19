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
#include "player.h"
#include "items.h"
#include <vector>

class Game_View
{
private:
    QGraphicsScene* scene;
    Camera* camera;
    std::vector<Player*> players_list;
    std::vector<Items*> items_list;

public:
    Game_View();
    Game_View(QRect screen, int w, int h);
    ~Game_View();
    void update_view();
    void add_Item(QGraphicsItem *item, int posx, int posy);
    void del_Item(Items *item);
    void setBackground(std::string& path);
    QGraphicsItem *itemAt(int posx,int posy);
    Camera *getCamera();
    Worm_View *getWormActive();   // esto no se si tiene sentido...

    void centerScreen(QRect rect);
    void maximizateScreen();
    void minimizateScreen();
    void addWidget(QWidget *widget);

    void moveObjTo(int type, int id, int posX, int posY, int angle);
    void addItemToFollow(MovableItem *item);
    bool containsItem(Items *item);
    bool containsItem(int8_t id_typ, int32_t id);
    Items *getItem(int8_t id_type, int32_t id);
    QGraphicsScene *getScene();
    void setPlayerActive(Player *player);
    int getWidth();
    int getHeight();
    Worm_View* getWormActive2();
    void addCamera(Camera *camera);
};

#endif // GAME_VIEW_H
