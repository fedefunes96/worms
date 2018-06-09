#ifndef GAMECLASS_H
#define GAMECLASS_H
#include "game_view.h"
#include <QObject>
#include "controler.h"
#include "gamewindow.h"
#include <QTimer>

class GameClass : public QObject
{
    Q_OBJECT
public:
    GameClass(QRect screen,int w,int h);


    Player* getPlayer();
    Game_View* getGameView();

    std::vector<int> fireWeapon();
    bool isMyTurn();
    void checkRound(int id);
    Camera *getCamera();
    Worm_View *getWormActive();
    void connectController(Controler *controler);
private slots:
    void checkQueueEvent(QList<int> list);
    void checkDeadItem();
private:
    Game_View* game;
    Player* myPlayer;
    bool myTurn;

    QTimer *deadItemCollector;

    void attachWorm(int type, int id, int health);
    void updateItem(int type=999, int id=999, int posX=0, int posY=0, int angle=0);
    void updatePlayer(int type=999,int id=999, int ammo=-10, Worm_View* worm=nullptr);
    void removeItem(int type, int id);

    GameWindow *window;

};

#endif // GAMECLASS_H
