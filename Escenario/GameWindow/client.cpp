#include <QApplication>
#include "game_view.h"
#include "worm_view.h"

#include <QGraphicsRectItem>

#include "eventhandler.h"
#include "girder_view.h"

#include <QDebug>
#include <QDesktopWidget>

#include <QLabel>

#include <iostream>

#include "protocol.h"
#include "player.h"

#include "socket.h"

#include "gameclass.h"
#include "controler.h"

#include "mapSelection.h"
#include "roomcreator.h"
#include "waitRoom.h"
#include "clientmainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QList<std::string>>("QList<std::string>");
    //
    //QRect rect = a.desktop()->screenGeometry();

    std::string ip("127.0.0.1");
    std::string puerto("7777");
    Socket client(ip,puerto);

    Protocol protocol(client);

    //GameClass game(rect,10000,10000);

    Controler controler(&protocol);

    WaitRoom wait(&protocol);
    MapSelection map(&protocol);
    RoomCreator room(&wait,&protocol);
    map.connectControler(&controler);
    room.connectControler(&controler);
    wait.connectControler(&controler);

    //game.connectController(&controler);
    controler.start();
    clientMainWindow c(&map,&room,&protocol);
    c.show();
    //EventHandler *filter = new EventHandler(&a,&game,&protocol);
    //a.installEventFilter(filter);


    return a.exec();
}




























