#ifndef GAMECLASS_H
#define GAMECLASS_H
#include "game_view.h"
#include <QObject>
#include "controler.h"
#include "gamewindow.h"
#include <QTimer>
#include <QList>
#include <vector>
#include "backgrounMusic.h"
#include "generalSounds.h"
#include "waitRoom.h"


class GameClass : public QObject
{
    Q_OBJECT
public:
    GameClass(QRect screen,int w,int h,int idply);
    ~GameClass();

    Player* getPlayer();
    Game_View* getGameView();

    std::vector<int> fireWeapon();
    bool isMyTurn();
    void checkRound(QList<int> list);
    Camera *getCamera();
    Worm_View *getWormActive();
    void connectController(Controler *controler);
    void setStatusWorm(QList<int> list);
    void setPotBar(int pot);
    void setRefocus(bool enable);
    void connectWaitRoom(WaitRoom *wait);
signals:
    void isWinner(bool iswinner);
private slots:
    void checkQueueEvent(QList<int> list);
    void checkDeadItem();
    void updateScreen();
    void showWindow();
private:
    Game_View* game;
    Player* myPlayer;
    bool myTurn;
    QList<QString> color_list;

    QTimer *deadItemCollector;
    QTimer *refreshScreen;

    void attachWorm(int type, int id_player, int id, int health);
    void updateItem(int type=999, int id=999, int posX=0, int posY=0, int angle=0);
    void updatePlayer(int type=999,int id=999, int ammo=-10, Worm_View* worm=nullptr);
    void removeItem(int type, int id);

    GameWindow *window;

    backgrounMusic* backGround;
    std::vector<generalSounds*> fall;
    std::vector<generalSounds*> fire;
    std::vector<generalSounds*>jumps;
    std::vector<generalSounds*>select;
    std::vector<generalSounds*>weaponSelect;
    generalSounds* explocion;


    void recvWormHealth(int id, int health);
    void throwProjectile(int type, int id, int posX, int posY, int angle, std::string &path);
};

#endif // GAMECLASS_H
