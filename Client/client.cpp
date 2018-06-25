#include <QApplication>
#include "stage.h"
#include "worm_view.h"
#include <QGraphicsRectItem>
#include "eventhandler.h"
#include "girder_view.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QLabel>
#include <iostream>
#include "protocol_client.h"
#include "player.h"
#include "game.h"
#include "controller.h"
#include "roomselector.h"
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
        ConectionWindow mainWindow;
        mainWindow.exec();
        if(mainWindow.closeWithX()){
            gameOpen=false;
            continue;
        }
        Socket client = mainWindow.getSocket();
        ProtocolClient protocol(client);
        Controller controler(&protocol);
        FinalScreen finalScreen(&a);
        WaitRoom wait(&protocol);
        RoomSelector map(&protocol);
        RoomCreator room(&protocol);
        map.connectControler(&controler);
        room.connectControler(&controler);
        wait.connectControler(&controler);
        Window c(&protocol);
        c.connectControler(&controler);
        controler.start();
        Game game(&a);
        game.connectWaitRoom(&wait);
        game.connectController(&controler);
        finalScreen.connectGame(&game);
        bool windowRunning = true;
        while (windowRunning){
            c.exec();
            game.setIdPlayer(c.getId());
            if(c.isSelectRoom()){
                //ejecutar ventana de seleccion de sala
                c.cleanCond();
                map.setExecute(true);
                map.askRooms();
                map.exec();
                if(map.closeWithX()){
                    controler.terminate();
                    windowRunning=false;
                    map.cleanCond();
                    continue;
                }else if(map.isCallBack()){
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
                    controler.terminate();
                    windowRunning=false;
                    room.cleanCond();
                    continue;
                }else if(room.isCallBack()){
                    room.cleanCond();
                    continue;
                }
            }else if(c.closeWithX()){
                //cerrar todo!!!
                c.cleanCond();
                windowRunning=false;
                continue;
            }
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




























