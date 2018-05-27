#ifndef GAME_H
#define GAME_H
#include "protocol.h"
#include "player.h"
#include "game_view.h"
#include <QThread>
#include <QApplication>


class Game: public QThread
{
public:
    Game(Protocol* protocol,Player* player, Game_View* game_view, QApplication* app);
    void run();

private:
    Protocol* protocol;
    Player* player;
    Game_View* game_view;
    QApplication* app;

};

#endif // GAME_H
