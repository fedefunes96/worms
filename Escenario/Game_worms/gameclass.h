#ifndef GAMECLASS_H
#define GAMECLASS_H
#include "game_view.h"
#include <QTimer>
#include <QObject>
#include <QQueue>
#include "eventgame.h"


class GameClass : public QObject
{
public:
    GameClass(QRect screen,int w,int h);

    void updateItem(int type=999,int id=999,int health=-10, int posX=0, int posY=0, int angle=0);
    void updatePlayer(int type=999,int id=999, int ammo=-10, Worm_View* worm=nullptr);

    void addEvent(EventGame event);


    Player* getPlayer();
    Game_View* getGameView();

    void timerStop();
    void moveWorm();
private slots:
    void prueba();
    void prueba2();
    void checkQueueEvent();
private:
    Game_View* game;
    Player* myPlayer;
    QTimer *timer;
    QQueue<EventGame> *queue;
};

#endif // GAMECLASS_H
