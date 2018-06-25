#include "controller.h"
#include <QTimer>
#include "worm_view.h"
#include <iostream>

Controller::Controller(ProtocolClient *protocol)
{
    this->protocol = protocol;
}

void Controller::stopController()
{
    this->terminate();
}

void Controller::run()
{
    bool gameRunning=true;
    while(gameRunning){
        QList<int> list;
        int8_t cmd = this->protocol->recvCmd();
        list.push_back(cmd);
        if(cmd== static_cast<int>(Commands::GAME_END)){
            gameRunning=false;
            return;
        }else if(cmd==static_cast<int>(Commands::ATTACH_PLAYER_ID)){
            int8_t id;
            this->protocol->recvPlayerId(&id);
            emit playerId(id);
            continue;
        }else if(cmd==static_cast<int>(Commands::ATTACH_USABLE_ID)){
            int8_t id_weapon;
            int32_t ammo;
            this->protocol->recvUsableId(&id_weapon,&ammo);
            list.push_back(id_weapon);
            list.push_back(ammo);
            emit eventCreated(list);
            continue;
        }else if(cmd==static_cast<int>(Commands::ACTUAL_PLAYER)){
            int8_t id;
            int8_t id_worm;
            this->protocol->recvActualPlayer(&id,&id_worm);
            list.push_back(id);
            list.push_back(id_worm);
            emit eventCreated(list);
            continue;
        }else if(cmd==static_cast<int>(Commands::ATTACH_WORM_ID)){
            int8_t id;
            int32_t health;
            int8_t id_player;
            this->protocol->recvWormId(&id_player,&id,&health);
            list.push_back(id_player);
            list.push_back(id);
            list.push_back(health);
            emit eventCreated(list);
            continue;
        }else if(cmd==static_cast<int>(Commands::REMOVE)){
            int8_t id_obj;
            int32_t id;
            this->protocol->recvRemove(&id_obj,&id);
            list.push_back(id_obj);
            list.push_back(id);
            emit eventCreated(list);
            continue;
        }else if(cmd == static_cast<int>(Commands::WORM_STATUS)){
            int8_t idworm;
            int8_t on_ground;
            int8_t dir;
            this->protocol->recvWormStatus(&idworm,&on_ground,&dir);
            list.push_back(idworm);
            list.push_back(on_ground);
            list.push_back(dir);
            emit eventCreated(list);
        }else if(cmd==static_cast<int>(Commands::POSITION)){
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
            emit eventCreated(list);
            continue;
        }else if(cmd==static_cast<int>(Commands::WIND_PARAMS)){
            int32_t min;
            int32_t max;
            this->protocol->recvWindParamt(&min,&max);
            list.push_back(min);
            list.push_back(max);
            emit eventCreated(list);
            continue;
        }else if(cmd==static_cast<int>(Commands::WIND_SPEED)){
            int32_t speed;
            this->protocol->recvWindSpeed(&speed);
            list.push_back(speed);
            emit eventCreated(list);
            continue;
        }else if(cmd==static_cast<int>(Commands::WINNER)){
            int8_t id;
            this->protocol->recvWinner(&id);
            gameRunning=false;
            list.push_back(id);
            emit eventCreated(list);
        }else if(cmd==static_cast<int>(Commands::WORM_HEALTH)){
            int8_t id;
            int32_t health;
            this->protocol->recvWormHealth(&id,&health);
            list.push_back(id);
            list.push_back(health);
            emit eventCreated(list);
        } else if (cmd==static_cast<int>(Commands::MAP_LIST)){
        	std::vector<std::string> names;
        	this->protocol->recvMaps(names);
            QList<std::string> name = QList<std::string>::fromVector(QVector<std::string>::fromStdVector(names));
            emit recvMap(name);
        } else if (cmd==static_cast<int>(Commands::SHOW_ROOMS)){
        	std::vector<std::string> names;
        	this->protocol->recvRomms(names);
            QList<std::string> name = QList<std::string>::fromVector(QVector<std::string>::fromStdVector(names));
            emit recvMap(name);
        } else if (cmd==static_cast<int>(Commands::COULD_JOIN)){
        	int8_t conecto = this->protocol->recvCouldJoinRoom();
        	list.push_back(conecto);
            emit joinR(conecto);
        } else if (cmd==static_cast<int>(Commands::PLAYERS_IN_ROOM)){
        	int8_t cant = this->protocol->recvPlayersInRoom();
        	list.push_back(cant);
            emit playersInRoom(cant);
        } else if (cmd==static_cast<int>(Commands::START_GAME)){
            std::string nameBack = this->protocol->recvBackground();
            QList<std::string> nameback;
            nameback.push_back(nameBack);
            emit startGame(nameback);
        }
    }

  }
