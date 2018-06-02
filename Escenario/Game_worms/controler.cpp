#include "controler.h"
#include "eventgame.h"

#include <QTimer>
#include "worm_view.h"

Controler::Controler(Protocol *protocol, GameClass *game)
{
    this->protocol = protocol;
    this->game = game;
    //timer = new QTimer();
    //timer->start(3000);
}


void Controler::prueba(){
    qDebug()<<"lance";
    //this->game->timerStop();
}

void Controler::run()
{
/*
    EventGame ev;
    ev.typeEvent=0;
    ev.id=0;
    ev.posX=100;
    ev.posY=100;
    ev.health=-10;
    ev.angle=0;
    this->game->addEvent(ev);
    return;
*/

    bool gameRunning=true;
    while(gameRunning){ // temporal
        EventGame event;
        int8_t cmd = this->protocol->recvCmd();
        event.typeEvent=cmd;

        if(cmd== static_cast<int>(Commands::GAME_END)){
            qDebug()<<"game end";
            gameRunning=false;
            //avisar a game
            return;
        }else if(cmd==static_cast<int>(Commands::ATTACH_PLAYER_ID)){
            qDebug()<<"attach player id";
            int8_t id;
            this->protocol->recvPlayerId(&id);
            event.id=id;
            this->game->addEvent(event);
            continue;
        }else if(cmd==static_cast<int>(Commands::ATTACH_USABLE_ID)){
            qDebug()<<"attach usable id";
            int8_t id_weapon;
            int32_t ammo;
            this->protocol->recvUsableId(&id_weapon,&ammo);
            this->game->updatePlayer(cmd,id_weapon,ammo);
            event.ammo = ammo;
            event.id = id_weapon;
            this->game->addEvent(event);
            continue;
        }else if(cmd==static_cast<int>(Commands::ACTUAL_PLAYER)){
            qDebug()<<"actual player";
            int8_t id;
            this->protocol->recvActualPlayer(&id);
            //Enable key control..
            continue;
        }else if(cmd==static_cast<int>(Commands::ATTACH_WORM_ID)){
            qDebug()<<"attach worm id";
            int8_t id;
            int32_t health;
            this->protocol->recvWormId(&id,&health);
            event.id=id;
            event.typeObj = static_cast<int>(TypeObj::WORM);
            event.health = health;
            this->game->addEvent(event);
            continue;
        }else if(cmd==static_cast<int>(Commands::REMOVE)){
            //qDebug()<<"remove";
            int8_t id_obj;
            int32_t id;
            this->protocol->recvRemove(&id_obj,&id);
            //Remove item
            continue;
        }else if(cmd==static_cast<int>(Commands::POSITION)){
            //qDebug()<<"position";
            int8_t obj_type=0;
            int32_t id_obj=0;
            int32_t posX=0;
            int32_t posY=0;
            int32_t angle=0;
            this->protocol->recvPosition(&obj_type,&id_obj,&posX,&posY,&angle);
            event.typeObj=obj_type;
            event.id = id_obj;
            event.posX = posX;
            event.posY = posY;
            event.angle = angle;
            event.health = -10;
            this->game->addEvent(event);
            continue;
        }else if(cmd==static_cast<int>(Commands::WINNER)){
            qDebug()<<"Winner!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
            this->game->addEvent(event);
            gameRunning=false;
        }
    }

  }
