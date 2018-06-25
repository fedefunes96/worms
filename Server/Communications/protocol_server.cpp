#include "socket.h"
#include "protocol.h"
#include "protocol_server.h"
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <mutex>
#include <iostream>

ProtocolServer::ProtocolServer(Socket& conexion) : Protocol(conexion) {}

void ProtocolServer::sendPosition(const std::string& type_obj
	, int32_t id_obj
	, float posX
	, float posY
	, float angle) {
    TypeObj type;
    Commands cmd = Commands::POSITION;

    if (type_obj.compare("Worm")==0) {
        type = TypeObj::WORM;
    } else if (type_obj.compare("LargeGirder")==0) {
        type = TypeObj::LARGE_GIRDER;
    } else if (type_obj.compare("SmallGirder")==0) {
        type = TypeObj::SMALL_GIRDER;
    } else if (type_obj.compare("Bazooka")==0) {
        type = TypeObj::BAZOOKA_M;
    } else if (type_obj.compare("Mortar")==0) {
        type = TypeObj::MORTAR_M;
    } else if (type_obj.compare("Fragment")==0) {
        type = TypeObj::FRAGMENT_M;
    } else if (type_obj.compare("GreenGrenade")==0) {
        type = TypeObj::GREEN_GRENADE_M;
    } else if (type_obj.compare("RedGrenade")==0) {
        type = TypeObj::RED_GRENADE_M;
    } else if (type_obj.compare("Banana")==0) {
        type = TypeObj::BANANA_M;
    } else if (type_obj.compare("HolyGrenade")==0) {
        type = TypeObj::HOLY_GRENADE_M;
    } else if (type_obj.compare("Dynamite")==0) {
        type = TypeObj::DYNAMITE_M;
    } else if (type_obj.compare("AerialAttack")==0) {
        type = TypeObj::AERIAL_ATTACK_M;
    }

    this->send_cmd(cmd);
    this->send_type_obj(type);
    this->send_int_unsigned(id_obj);
    this->send_int_signed(static_cast<int>(posX*10000));
    this->send_int_signed(static_cast<int>(posY*10000));
    this->send_int_signed(static_cast<int>(angle*100));
}

void ProtocolServer::sendWormId(int8_t id, int8_t id_worm, int32_t health) {
    Commands cmd = Commands::ATTACH_WORM_ID;

    this->send_cmd(cmd);
    this->send_char(id);
    this->send_char(id_worm);
    this->send_int_unsigned(health);
}

void ProtocolServer::sendWormStatus(int8_t id, bool ground,int8_t dir){
    Commands cmd = Commands::WORM_STATUS;
    int8_t on_ground = 0;

    if (ground) {
        on_ground=1;
    }    

    this->send_cmd(cmd);
    this->send_char(id);
    this->send_char(on_ground);
    this->send_char(dir);
}

void ProtocolServer::sendUsableId(int8_t id, int32_t ammo) {
    Commands cmd = Commands::ATTACH_USABLE_ID;

    this->send_cmd(cmd);
    this->send_char(id);
    this->send_int_signed(ammo);
}

void ProtocolServer::sendPlayerId(int8_t id) {
    Commands cmd = Commands::ATTACH_PLAYER_ID;

    this->send_cmd(cmd);
    this->send_char(id);
}

void ProtocolServer::sendRemove(const std::string& type_obj, int32_t id) {
    Commands cmd = Commands::REMOVE;    
    TypeObj type;

    if (type_obj.compare("Worm")==0) {
        type = TypeObj::WORM;
    } else if (type_obj.compare("LargeGirder")==0) {
        type = TypeObj::LARGE_GIRDER;
    } else if (type_obj.compare("SmallGirder")==0) {
        type = TypeObj::SMALL_GIRDER;
    } else if (type_obj.compare("Bazooka")==0) {
        type = TypeObj::BAZOOKA_M;
    } else if (type_obj.compare("Mortar")==0) {
        type = TypeObj::MORTAR_M;
    } else if (type_obj.compare("Fragment")==0) {
        type = TypeObj::FRAGMENT_M;
    } else if (type_obj.compare("GreenGrenade")==0) {
        type = TypeObj::GREEN_GRENADE_M;
    } else if (type_obj.compare("RedGrenade")==0) {
        type = TypeObj::RED_GRENADE_M;
    } else if (type_obj.compare("Banana")==0) {
        type = TypeObj::BANANA_M;
    } else if (type_obj.compare("HolyGrenade")==0) {
        type = TypeObj::HOLY_GRENADE_M;
    } else if (type_obj.compare("Dynamite")==0) {
        type = TypeObj::DYNAMITE_M;
    } else if (type_obj.compare("AerialAttack")==0) {
        type = TypeObj::AERIAL_ATTACK_M;
    }

    this->send_cmd(cmd);
    this->send_type_obj(type);
    this->send_int_unsigned(id);
}

void ProtocolServer::sendGameEnd() {
    Commands cmd = Commands::GAME_END;

    this->send_cmd(cmd);
}

void ProtocolServer::sendActualPlayer(int8_t id, int8_t worm_id) {
    Commands cmd = Commands::ACTUAL_PLAYER;  

    this->send_cmd(cmd);
    this->send_char(id);
    this->send_char(worm_id);
}

void ProtocolServer::sendWinner(int8_t id) {
    Commands cmd = Commands::WINNER;  

    this->send_cmd(cmd);
    this->send_char(id);
}

void ProtocolServer::sendWormHealth(int8_t id, int32_t health) {
    Commands cmd = Commands::WORM_HEALTH;  

    this->send_cmd(cmd);
    this->send_char(id);
    this->send_int_unsigned(health);
}

void ProtocolServer::sendDisconnect() {
    Commands cmd = Commands::DISCONNECT;  

    this->send_cmd(cmd);
}

void ProtocolServer::sendCouldJoinRoom(int8_t id) {
    Commands cmd = Commands::COULD_JOIN;  

    this->send_cmd(cmd);
    this->send_char(id);
}

void ProtocolServer::sendPlayersInRoom(int8_t size) {
    Commands cmd = Commands::PLAYERS_IN_ROOM;  

    this->send_cmd(cmd);
    this->send_char(size);
}

void ProtocolServer::sendStartGame(const std::string& background) {
    Commands cmd = Commands::START_GAME;  

    this->send_cmd(cmd);
    this->send_string(background);
}

void ProtocolServer::sendWindParams(float min, float max) {
    Commands cmd = Commands::WIND_PARAMS; 

    this->send_cmd(cmd);
    this->send_int_unsigned(static_cast<int>(min*100));
    this->send_int_unsigned(static_cast<int>(max*100));
}

void ProtocolServer::sendWindSpeed(float speed) {
    Commands cmd = Commands::WIND_SPEED; 

    this->send_cmd(cmd);
    this->send_int_signed(static_cast<int>(speed*100));
}

void ProtocolServer::sendRooms(const std::vector<std::string>& rooms_name) {
    Commands cmd = Commands::SHOW_ROOMS;  

    int8_t size = (int8_t) rooms_name.size();

    this->send_cmd(cmd);
    this->send_char(size);

    for (int i = 0; i < (int) rooms_name.size(); i++) {
    	this->send_string(rooms_name[i]);
    }
}

void ProtocolServer::sendMaps(const std::vector<std::string>&maps) {
    Commands cmd = Commands::MAP_LIST;

    int8_t size = (int8_t) maps.size();

    this->send_cmd(cmd);

    this->send_char(size);
    for (int i = 0; i < (int) maps.size(); i++) {
        this->send_string(maps[i]);
    } 
}

void ProtocolServer::recvRoom(std::string& room_name) {
    room_name = this->recv_string(); 
}

void ProtocolServer::recvCreateRoom(std::string& room_name, std::string& stage_file) {
	room_name = this->recv_string();
	stage_file = this->recv_string();
}

void ProtocolServer::recvMove(int *dir) {
	*dir = this->recv_char();
}

void ProtocolServer::recvAttack(int* id_weapon, int* posx, int* posy, std::vector<int>& params) {    
    UsableIds uid = this->recv_usable();
    *id_weapon = static_cast<int>(uid);

    *posx = this->recv_int_unsigned();
    *posy = this->recv_int_unsigned();

    switch (uid) {
        case UsableIds::BAZOOKA: {
            params.push_back(this->recv_int_unsigned());
            break;
        }
        case UsableIds::MORTAR: {
            params.push_back(this->recv_int_unsigned());
            break;
        }  
        case UsableIds::GREEN_GRENADE: {
            params.push_back(this->recv_int_unsigned());
            params.push_back(this->recv_int_unsigned());            
            break;
        }   
        case UsableIds::RED_GRENADE: {
            params.push_back(this->recv_int_unsigned());
            params.push_back(this->recv_int_unsigned());
            break;
        }   
         case UsableIds::BANANA: {
            params.push_back(this->recv_int_unsigned());
            params.push_back(this->recv_int_unsigned());         
            break;
        }   
        case UsableIds::HOLY_GRENADE: {
			params.push_back(this->recv_int_unsigned());
			params.push_back(this->recv_int_unsigned());         
            break;
        } 
        case UsableIds::DYNAMITE: {
            params.push_back(this->recv_int_unsigned());         
            break;
        }     
        default: break;                                          
    }
}
