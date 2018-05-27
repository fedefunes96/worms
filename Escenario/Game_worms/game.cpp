#include "game.h"
#include "girder_view.h"
#include "worm_view.h"
#include "eventhandler.h"
#include <QDebug>


Game::Game(Protocol *protocol, Player *player, Game_View *game_view, QApplication* app):
                                                protocol(protocol),
                                                player(player),
                                                game_view(game_view),
                                                app(app)
{

/*
    Worm_View* worm = new Worm_View();


    worm->setSelected(true);


    this->game_view->add_Item(worm,600,220);
    worm->setVida(100);
    worm->set_idWorm(5);
    worm->setDir(worm->x(),worm->y());

    Girder_View* girder = new Girder_View(0,140);
    girder->setZValue(-3);
    this->game_view->add_Item(girder,450,170);

    Girder_View* girder2 = new Girder_View(5,140);
    girder->setZValue(-3);
    this->game_view->add_Item(girder2,500,200);

    //this->game_view->getCamera()->addItemToFollow(worm);


    Worm_View* worm4 = new Worm_View();
    worm4->set_idWorm(7);
    Worm_View* worm5 = new Worm_View();
    worm5->set_idWorm(6);
    Girder_View* girder4 = new Girder_View(90,140);
    Girder_View* girder5 = new Girder_View(45,70);
    this->game_view->add_Item(worm4,0,0);
    this->game_view->add_Item(worm5,200,200);
    this->game_view->add_Item(girder4,300,300);
    this->game_view->add_Item(girder5,300,300);

*/



    int8_t my_id;
    my_id = protocol.recvId();
    Player* my_player = new Player();
    my_player->setId(my_id);

    int8_t cantidad;
    cantidad = protocol.recvByte();
    for (int var = 0; var < cantidad; ++var) {
        int8_t id_player;
        int8_t cant_worms;
        id_player=protocol.recvId();
        cant_worms = protocol->recvByte();
        Player* player = new Player();
        player->setId(id_player);
        for (int var2 = 0; var2 < cant_worms; ++var2) {

            int8_t id_worm;
            int8_t vida;
            int32_t posX;
            int32_t posY;
            int8_t angle;
            protocol->recvObj(&id_worm,&vida,&posX,&posY,&angle);

            Worm_View* worm = new Worm_View();
            worm->setLife(vida);
            worm->set_idWorm(id_worm);
            this->game_view->add_Item(worm,posX,posY);
            player->addWorm(worm);
        }
    }

    cantidad = protocol->recvByte();
    for (int var = 0; var < cantidad; ++var) {
        int8_t id;
        int32_t posX;
        int32_t posY;
        int8_t angle;
        protocol->recvObj(&id,&posX,&posY,&angle);
        Girder_View* girder = new Game_View(-angle,id);
        my_game.add_Item(girder,posX,posY);
    }





    EventHandler *filter = new EventHandler(this->app,this->game_view);
    this->app->installEventFilter(filter);


}






void Game::run()
{

    //this->game_view->moveObjTo(7,100,100,0);

}
