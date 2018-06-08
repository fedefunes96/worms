#include "controler.h"

#include <QTimer>
#include "worm_view.h"

Controler::Controler(Protocol *protocol)
{
    this->protocol = protocol;
    //timer = new QTimer();
    //timer->start(3000);
}


void Controler::prueba(){
    qDebug()<<"lance";
    //this->game->timerStop();
}

void Controler::run()
{

    bool gameRunning=true;
    while(gameRunning){ // temporal
        QList<int> list;
        int8_t cmd = this->protocol->recvCmd();
        list.push_back(cmd);
        if(cmd== static_cast<int>(Commands::GAME_END)){
            qDebug()<<"game end";
            gameRunning=false;
            //avisar a game con emit
            return;
        }else if(cmd==static_cast<int>(Commands::ATTACH_PLAYER_ID)){
            qDebug()<<"attach player id";
            int8_t id;
            this->protocol->recvPlayerId(&id);
            list.push_back(id);
            //this->game->addEvent(event);
            emit eventCreated(list);
            continue;
        }else if(cmd==static_cast<int>(Commands::ATTACH_USABLE_ID)){
            qDebug()<<"attach usable id";
            int8_t id_weapon;
            int32_t ammo;
            this->protocol->recvUsableId(&id_weapon,&ammo);
            list.push_back(id_weapon);
            list.push_back(ammo);
            //this->game->addEvent(event);  UPDATE WEAPON TO USE
            emit eventCreated(list);
            continue;
        }else if(cmd==static_cast<int>(Commands::ACTUAL_PLAYER)){
            qDebug()<<"actual player";
            int8_t id;
            this->protocol->recvActualPlayer(&id);
            //Enable key control..
            list.push_back(id);
            //this->game->addEvent(event);    ACTUAL PLAYER
            emit eventCreated(list);
            continue;
        }else if(cmd==static_cast<int>(Commands::ATTACH_WORM_ID)){
            qDebug()<<"attach worm id";
            int8_t id;
            int32_t health;
            this->protocol->recvWormId(&id,&health);
            list.push_back(id);            
            list.push_back(health);
            qDebug()<<"id:"<<id<<"vida"<<health;

            //this->game->addEvent(event);    DEFINE WORM
            emit eventCreated(list);
            continue;
        }else if(cmd==static_cast<int>(Commands::REMOVE)){
            qDebug()<<"remove";
            int8_t id_obj;
            int32_t id;
            this->protocol->recvRemove(&id_obj,&id);

            list.push_back(id_obj);
            list.push_back(id);
            qDebug()<<"----->>>>>>>>>   id OBJ:"<<id_obj<<"id:"<<id;
            //Remove item     REMOVE ITEM
            emit eventCreated(list);
            continue;
        }else if(cmd==static_cast<int>(Commands::POSITION)){
            //qDebug()<<"position";
            int8_t obj_type=0;
            int32_t id_obj=0;
            int32_t posX=0;
            int32_t posY=0;
            int32_t angle=0;
            this->protocol->recvPosition(&obj_type,&id_obj,&posX,&posY,&angle);

            list.push_back(obj_type);
            list.push_back(id_obj);
            list.push_back(posX);
            list.push_back(posY);
            list.push_back(angle);

            //this->game->addEvent(event);
            if(id_obj==0 && obj_type==0){
                qDebug()<<"--> x:"<<posX<<"y:"<<posY;
            }
            emit eventCreated(list);
            continue;
        }else if(cmd==static_cast<int>(Commands::WINNER)){
            qDebug()<<"Winner!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
            //this->game->addEvent(event);
            gameRunning=false;
            emit eventCreated(list);
        }
    }

  }
