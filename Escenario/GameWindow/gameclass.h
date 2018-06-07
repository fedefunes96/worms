#ifndef GAMECLASS_H
#define GAMECLASS_H
#include "game_view.h"
#include <QObject>
#include "controler.h"

class GameClass : public QObject
{
    Q_OBJECT
public:
    GameClass(QRect screen,int w,int h);

    void updateItem(int type=999,int id=999,int health=-10, int posX=0, int posY=0, int angle=0);
    void updatePlayer(int type=999,int id=999, int ammo=-10, Worm_View* worm=nullptr);

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
private:
    Game_View* game;
    Player* myPlayer;
    bool myTurn;

};

#endif // GAMECLASS_H
