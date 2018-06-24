#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <QObject>
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
#include <QTimer>

class Game_View: public QObject
{
private:
    QGraphicsScene* scene;
    Camera* camera;
    std::vector<Player*> players_list;
    std::vector<Items*> items_list;
    QTimer *timerUpdate;

private slots:
    void update_view();

public:
    Game_View();
    ~Game_View();
    Game_View(int w, int h);
    void add_Item(QGraphicsItem *item, int posx, int posy);
    void setBackground(std::string& path);
    QGraphicsItem *itemAt(int posx,int posy);
    Camera *getCamera();
    void addWidget(QWidget *widget);
    void moveObjTo(int type, int id, int posX, int posY, int angle);
    void addItemToFollow(MovableItem *item);
    bool containsItem(int8_t id_typ, int32_t id);
    Items *getItem(int8_t id_type, int32_t id);
    QGraphicsScene *getScene();
    void setPlayerActive(Player *player);
    int getWidth();
    int getHeight();
    void addCamera(Camera *camera);
    void resizeScene(int w, int h);
};

#endif // GAME_VIEW_H
