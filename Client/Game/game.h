#ifndef GAME_H
#define GAME_H
#include "stage.h"
#include <QObject>
#include "controller.h"
#include "gamewindow.h"
#include <QTimer>
#include <QList>
#include "waitRoom.h"
#include "backgrounMusic.h"
#include <QApplication>


class Game : public QObject
{
    Q_OBJECT
public:
    Game(QApplication *app);
    ~Game();
    Player* getPlayer();
    Stage* getGameView();
    std::vector<int> fireWeapon();
    bool isMyTurn();
    void checkRound(QList<int> list);
    Camera *getCamera();
    void connectController(Controller *controler);
    void setStatusWorm(QList<int> list);
    void setPotBar(int pot);
    void connectWaitRoom(WaitRoom *wait);
    void setRefocus(bool enable);
    void setIdPlayer(int id);
signals:
    void isWinner(bool iswinner);
private slots:
    void checkQueueEvent(QList<int> list);
    void checkDeadItem();
    void showWindow(QList<std::string> list);
private:
    Stage* game;
    Player* myPlayer;
    bool myTurn;
    QList<QString> color_list;
    QList<Player*> players_list;
    QTimer *deadItemCollector;
    void attachWorm(int type, int id_player, int id, int health);
    void updateItem(int type=999, int id=999, int posX=0, int posY=0, int angle=0);
    void updatePlayer(int type=999,int id=999, int ammo=-10, Worm_View* worm=nullptr);
    void removeItem(int type, int id);
    GameWindow *window;
    backgrounMusic *b;
    void recvWormHealth(int id, int health);
    void throwProjectile(int type, int id, int posX, int posY, int angle, std::string &path);
    void createColorList();
    QString getColor(int id_player);
    Player *getPlayerInList(int id_player);
    Player *lastP;
    QApplication *app;
};

#endif // GAMECLASS_H
