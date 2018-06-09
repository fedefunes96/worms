#include "protocol.h"
#include <iostream>

Protocol::Protocol(Socket& conexion) : conexion(conexion) {}
//Server 
//Server 
void Protocol::sendPosition(const std::string& type_obj, int32_t id_obj, float posX, float posY, float angle) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    TypeObj type;
    Commands cmd = Commands::POSITION;

    if (type_obj.compare("Worm")==0) {
        type = TypeObj::WORM;
    } else if (type_obj.compare("Girder")==0) {
        type = TypeObj::GIRDER;
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

    int32_t conv_id = htonl(id_obj); 
    int32_t conv_posx = htonl(static_cast<int>(posX*10000));
    int32_t conv_posy = htonl(static_cast<int>(posY*10000));
    int32_t conv_angle = htonl(static_cast<int>(angle*100));

    //char c = static_cast<std::underlying_type<Commands>::type>(cmd);

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&type,1);
    conexion.enviar((const char*)&conv_id,4);
    conexion.enviar((const char*)&conv_posx,4);
    conexion.enviar((const char*)&conv_posy,4);
    conexion.enviar((const char*)&conv_angle,4);

    //std::cout << "angulo:" <<angle*100 << "-" << id_obj << "-" << posX << "-" << posY << std::endl;
}

void Protocol::sendWormId(int8_t id, int32_t health) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    int32_t conv_health = htonl(health); 

    Commands cmd = Commands::ATTACH_WORM_ID;

    //char c = static_cast<std::underlying_type<Commands>::type>(cmd);

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id,1);
    conexion.enviar((const char*)&conv_health,4);    
}

void Protocol::sendUsableId(int8_t id, int32_t ammo) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::ATTACH_USABLE_ID;

    int32_t conv_ammo = htonl(ammo);

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id,1);
    conexion.enviar((const char*)&conv_ammo,4);       
}

void Protocol::sendPlayerId(int8_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::ATTACH_PLAYER_ID;

    //char c = static_cast<std::underlying_type<Commands>::type>(cmd);

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id,1);
}

void Protocol::sendRemove(const std::string& type_obj, int32_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::REMOVE;    
    TypeObj type;

    if (type_obj.compare("Worm")==0) {
        type = TypeObj::WORM;
    } else if (type_obj.compare("Girder")==0) {
        type = TypeObj::GIRDER;
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

    int32_t conv_id = htonl(id); 

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&type,1);
    conexion.enviar((const char*)&conv_id,4);   
}

void Protocol::sendGameEnd() {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::GAME_END;

    conexion.enviar((const char*)&cmd,1);
}

void Protocol::sendActualPlayer(int8_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::ACTUAL_PLAYER;  

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id,1);
}

void Protocol::sendWinner(int8_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::WINNER;  

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id,1);
}

void Protocol::sendRooms(int8_t rooms)
{
    conexion.enviar((const char*)&rooms,1);
}

void Protocol::sendRoomCaract(int8_t room, int8_t cantMax, int8_t cantActual)
{
    conexion.enviar((const char*)&room,1);
    conexion.enviar((const char*)&cantMax,1);
    conexion.enviar((const char*)&cantActual,1);
}

void Protocol::recvMove(int* id, int *dir) {
    std::lock_guard<std::mutex> lock(this->server_recv_m);

    conexion.recibir((char*)id,1);
    conexion.recibir((char*)dir,1);
}

void Protocol::recvAttack(int* id_weapon, int* id_worm, int* posx, int* posy, std::vector<int>& params) {
    std::lock_guard<std::mutex> lock(this->server_recv_m);
    
    int8_t uid;
    conexion.recibir((char*)&uid,1);
    *id_weapon = uid;

    conexion.recibir((char*)id_worm,1);

    int32_t aux;

    conexion.recibir((char*)&aux,4);
    *posx = ntohl(aux);
    conexion.recibir((char*)&aux,4);
    *posy = ntohl(aux);

    std::vector<int> extra_params;

    UsableIds usid = static_cast<UsableIds>(uid);

    switch (usid) {
        case UsableIds::BAZOOKA: {
            conexion.recibir((char*)&aux,4);
            extra_params.push_back(ntohl(aux));
            break;
        }
        case UsableIds::MORTAR: {
            conexion.recibir((char*)&aux,4);
            extra_params.push_back(ntohl(aux));
            break;
        }  
        case UsableIds::GREEN_GRENADE: {
            conexion.recibir((char*)&aux,4);
            extra_params.push_back((ntohl(aux)));
            conexion.recibir((char*)&aux,4);
            extra_params.push_back((ntohl(aux)));            
            break;
        }   
        case UsableIds::RED_GRENADE: {
            conexion.recibir((char*)&aux,4);
            extra_params.push_back((ntohl(aux)));
            conexion.recibir((char*)&aux,4);
            extra_params.push_back((ntohl(aux)));            
            break;
        }   
         case UsableIds::BANANA: {
            conexion.recibir((char*)&aux,4);
            extra_params.push_back((ntohl(aux)));
            conexion.recibir((char*)&aux,4);
            extra_params.push_back((ntohl(aux)));           
            break;
        }   
        case UsableIds::HOLY_GRENADE: {
            conexion.recibir((char*)&aux,4);
            extra_params.push_back((ntohl(aux)));
            conexion.recibir((char*)&aux,4);
            extra_params.push_back((ntohl(aux)));            
            break;
        } 
        case UsableIds::DYNAMITE: {
            conexion.recibir((char*)&aux,4);
            params.push_back((ntohl(aux)));            
            break;
        }     
        default: break;                                          
    }

    params = std::move(extra_params);
}

int8_t Protocol::recvRoomSel()
{
    int8_t id;
    conexion.recibir((char*)&id,1);
    return id;
}

//------------------------------------






















// Client

// Client
int convMtToPx(float mt){
    float aux = ((mt*140)/6.0);
    return int(aux + 0.5);
}

int convPxToMt(int px){
    float aux = ((px*6)/140.0);
    //std::cout << "conver MT:" << (aux) << std::endl;
    return int(aux + 0.5);
}



void Protocol::sendMove(int8_t id_worm,int8_t dir)
{
    //state --> 1 = END     0 = START
    //dir --> 1 = RIGHT     0 = LEFT
    std::cout << "id:" << static_cast<int16_t>(id_worm) << "dir" << static_cast<int16_t>(dir) << std::endl;

    Commands cmd = Commands::MOVE;
    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id_worm,1);
    conexion.enviar((const char*)&dir,1);
}


void Protocol::recvPosition(int8_t *type_obj, int32_t *id_obj, int32_t *posX, int32_t *posY, int32_t *angle)
{
    conexion.recibir((char*)type_obj,1);
    int32_t aux;
    conexion.recibir((char*)&aux,4);
    *id_obj = ntohl(aux);
    conexion.recibir((char*)&aux,4);
    *posX = convMtToPx(ntohl(aux)/10000.0);
    conexion.recibir((char*)&aux,4);
    *posY = convMtToPx(ntohl(aux)/10000.0);
    conexion.recibir((char*)&aux,4);
    float aux2=(ntohl(aux)*57.2958/100)+0.5;
    int32_t aux3 = (int32_t) aux2;
    *angle = aux3;
}


int8_t Protocol::recvCmd() {
    uint8_t cmd;
    conexion.recibir((char*)&cmd,1);
    //std::cout << "command:" << static_cast<int16_t>(cmd) << std::endl;
    return cmd;
}

void Protocol::recvWormId(int8_t *id, int32_t *health)
{
    conexion.recibir((char*)id,1);
    int32_t aux;
    conexion.recibir((char*)&aux,4);
    *health = ntohl(aux);
    //std::cout << "idWorm:" << static_cast<int16_t>(*id) << "health:" << *health << std::endl;
}

void Protocol::recvPlayerId(int8_t *id)
{
    conexion.recibir((char*)id,1);
    //std::cout << "idPlayer:" << static_cast<int16_t>(*id) << std::endl;
}

void Protocol::recvUsableId(int8_t* id,int32_t* ammo)
{
    conexion.recibir((char*)id,1);
    int32_t aux;
    conexion.recibir((char*)&aux,4);
    *ammo= ntohl(aux);
}

int8_t Protocol::recvRooms()
{
    int8_t rooms;
    conexion.recibir((char*)&rooms,1);
    return rooms;
}

void Protocol::recvRoomCaratc(int8_t *room, int8_t *cantMax, int8_t *cantActual)
{
    conexion.recibir((char*)room,1);
    conexion.recibir(( char*)cantMax,1);
    conexion.recibir(( char*)cantActual,1);
}

void Protocol::sendRoomSel(int8_t id)
{
    conexion.enviar((const char*) &id,1);
}

void Protocol::recvRemove(int8_t* id_obj,int32_t* id)
{
    conexion.recibir((char*)id_obj,1);
    int32_t aux;
    conexion.recibir((char*)&aux,4);
    *id=ntohl(aux);
}

void Protocol::recvActualPlayer(int8_t* id)
{
    conexion.recibir((char*)id,1);
}


void Protocol::recvWinner(int8_t* id)
{
    conexion.recibir((char*)id,1);
}


void Protocol::sendAttack(int8_t id_weapon, int8_t id_worm, int32_t posX, int32_t posY)
{
    Commands cmd = Commands::ATTACK;
    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id_weapon,1);
    conexion.enviar((const char*)&id_worm,1);
    int32_t conv = htonl(convPxToMt(posX));
    conexion.enviar((const char*)&conv,4);
    conv = htonl(convPxToMt(posY));
    conexion.enviar((const char*)&conv,4);

    //std::cout << "idweapon:" << static_cast<int16_t>(id_weapon) << "id_worm:" << static_cast<int16_t>(id_worm) << "posX:"<<posX <<"posY:"<<posY << std::endl;

}

