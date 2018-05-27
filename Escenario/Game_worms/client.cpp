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
#include "game.h"

#include "socket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game_View my_game;

    // center de application
    QRect rect = a.desktop()->screenGeometry();
    my_game.centerScreen(rect);
    my_game.maximizateScreen();

    std::string path(":/images/intro2.jpg");
    my_game.setBackground(path);

    //std::string("127.0.0.1");
    std::string puerto("7777");
    //Socket client(ip,puerto);
    Socket client(puerto);

    Protocol protocol(&client);
    int8_t my_id = protocol.recvId();
    Player player;
    player.setId(my_id);

    Game game(&protocol,&player,&my_game,&a);
    game.start();

    /*
    QEventLoop loop;
    connect(&netobject, SIGNAL(done()), &loop, SLOT(quit()));
    connect(quitButton, SIGNAL(clicked()), &app, SLOT(quit()));
    netobject.start_long_lived_process_that_happens_on_other_thread();

    loop.exec(); // BLOCKING (non-busy) until quit() is called via the signal done()
    */


    return a.exec();
}
