#include <QApplication>
#include "game_view.h"
#include "worm_view.h"

#include <QGraphicsRectItem>

#include "eventhandler.h"
#include "girder_view.h"

#include <QDebug>
#include <QDesktopWidget>

#include <QLabel>

#include "mybutton.h"
#include <iostream>

#include "protocol.h"
#include "player.h"

#include "socket.h"

#include "gameclass.h"
#include "controler.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // center de application
    QRect rect = a.desktop()->screenGeometry();

    std::string ip("127.0.0.1");
    std::string puerto("7777");
    Socket client(ip,puerto);
    //Socket client(puerto,5);

    Protocol protocol(client);

    GameClass game(rect,10000,10000);


//    Updater up;
//    up.setGameToUpdate(&game);
//    up.setFunction(updateGame);
//    up.start();


    Controler controler(&protocol);

    game.connectController(&controler);
    controler.start();

    //game.updateItem(0,4,-10,100,100,0);
    //game.updateItem(0,5,-10,150,100,0);



    EventHandler *filter = new EventHandler(&a,&game,&protocol);
    a.installEventFilter(filter);


    return a.exec();
}




























