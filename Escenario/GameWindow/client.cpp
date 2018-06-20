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


#include "gameclass.h"
#include "controler.h"

#include "mapSelection.h"
#include "roomcreator.h"
#include "waitRoom.h"
#include "window.h"
#include "finalscreen.h"
#include "conectionwindow.h"

int main(int argc, char *argv[])
{
    bool gameOpen=true;
    while(gameOpen){
        QApplication a(argc, argv);
        qRegisterMetaType<QList<std::string>>("QList<std::string>");

        QRect rect = a.desktop()->screenGeometry();

        ConectionWindow mainWindow;
        mainWindow.exec();

        if(mainWindow.closeWithX()){
            gameOpen=false;
            continue;
        }

        Socket client = mainWindow.getSocket();

        Protocol protocol(client);

        Controler controler(&protocol);

        WaitRoom wait(&protocol);
        MapSelection map(&wait,&protocol);
        RoomCreator room(&wait,&protocol);
        FinalScreen finalScreen(&a);
        map.connectControler(&controler);
        room.connectControler(&controler);
        wait.connectControler(&controler);

        Window c(&map,&room,&protocol,&wait);

        c.connectControler(&controler);
        controler.start();
        c.exec();

        GameClass game(rect,500,500,c.getId());
        game.connectWaitRoom(&wait);
        game.connectController(&controler);

        finalScreen.connectGame(&game);

        if(c.closeWithX()){
            controler.terminate();
            continue;
        }

        if(!wait.getShowWindow()){
            continue;
        }
        qDebug()<<"PASEEEEEEEEEEE";
        wait.exec();

        EventHandler *filter = new EventHandler(&a,&game,&protocol);
        a.installEventFilter(filter);


        if(wait.closeWithX()){
            continue;
        }
        a.exec();//solucionar esto para cerrar el juego
    }
    return 0;
}




























