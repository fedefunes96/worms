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
        qDebug()<<"Inicio TODO";
        QApplication a(argc, argv);
        qRegisterMetaType<QList<std::string>>("QList<std::string>");
        //QRect rect = a.desktop()->screenGeometry();

        ConectionWindow mainWindow;
        mainWindow.exec();

        if(mainWindow.closeWithX()){
            gameOpen=false;
            continue;
        }

        Socket client = mainWindow.getSocket();
        Protocol protocol(client);
        Controler controler(&protocol);
        qDebug()<<"pase1111111111111111111";
        FinalScreen finalScreen(&a);

        WaitRoom wait(&protocol);

        MapSelection map(&protocol);
        RoomCreator room(&protocol);
        map.connectControler(&controler);
        room.connectControler(&controler);
        wait.connectControler(&controler);

        Window c(&protocol);
        c.connectControler(&controler);
        controler.start();


        GameClass game(&a);
        game.connectWaitRoom(&wait);
        game.connectController(&controler);
        qDebug()<<"pase11111111111111111112222222222";
        finalScreen.connectGame(&game);

        bool windowRunning = true;
        while (windowRunning){


            qDebug()<<"inicio ventana nuevamente..";
            c.exec();
            game.setIdPlayer(c.getId());
            qDebug()<<"pase 7";
            if(c.isSelectRoom()){
                //ejecutar ventana de seleccion de sala
                c.cleanCond();
                map.setExecute(true);
                map.askRooms();
                map.exec();
                if(map.closeWithX()){
                    qDebug()<<"CERRAR TODO DESDE ROOM SELECTOR";
                    controler.terminate();
                    windowRunning=false;
                    map.cleanCond();
                    continue;
                }else if(map.isCallBack()){
                    qDebug()<<"quiero volver atras con room selector";
                    map.cleanCond();
                    continue;
                }
            }else if(c.iscreateRoom()){
                //ejecutar ventana de creacion de sala
                c.cleanCond();
                room.setExecute(true);
                room.askMaps();
                room.exec();
                if(room.closeWithX()){
                    //cerrar todo!!!
                    qDebug()<<"CERRAR TODO DESDE ROOM CREATOR";
                    controler.terminate();
                    windowRunning=false;
                    room.cleanCond();
                    continue;
                }else if(room.isCallBack()){
                    qDebug()<<"quiero volver atras con room creator";
                    room.cleanCond();
                    continue;
                }
            }else if(c.closeWithX()){
                //cerrar todo!!!
                c.cleanCond();
                qDebug()<<"CERRAR TODO DESDE WINDOW";
                windowRunning=false;
                continue;
            }

            qDebug()<<"ACA DEBERIA IR LA VENTANA WAIT ROOM";
            wait.exec();
            if(wait.isExitRoom()){
                wait.cleanCond();
                c.cleanCond();
                map.cleanCond();
                room.cleanCond();
                continue;
            }else if(wait.closeWithX()){
                controler.terminate();
                windowRunning=false;
                wait.cleanCond();
                c.cleanCond();
                map.cleanCond();
                room.cleanCond();
                continue;

            }
            qDebug()<<"continua con el juego...";
            EventHandler *filter = new EventHandler(&a,&game,&protocol);
            a.installEventFilter(filter);
            a.exec();
            windowRunning=false;
            break;
        }
        if(windowRunning==false){
            gameOpen=false;
            controler.terminate();
            continue;
        }



    }
    return 0;
}




























