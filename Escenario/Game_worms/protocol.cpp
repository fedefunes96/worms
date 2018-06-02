#include "protocol.h"
#include <iostream>

Protocol::Protocol(Socket *conexion) : conexion(conexion) {}

Protocol::Protocol(Protocol&& other) : conexion(other.conexion) {
    other.conexion = nullptr;
}
//Server 
void Protocol::sendPosition(std::string type_obj, int32_t id_obj, float posX, float posY, float angle) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    TypeObj type;
    Commands cmd = Commands::POSITION;

    if (type_obj.compare("Worm")) {
        type = TypeObj::WORM;
    } else if (type_obj.compare("Girder")) {
        type = TypeObj::GIRDER;
    } else if (type_obj.compare("Bazooka")) {
        type = TypeObj::BAZOOKA_M;
    }

    int32_t conv_id = htonl(id_obj); 
    int32_t conv_posx = htonl(static_cast<int>(posX));
    int32_t conv_posy = htonl(static_cast<int>(posY));
    int32_t conv_angle = htonl(static_cast<int>(angle*100));

    //char c = static_cast<std::underlying_type<Commands>::type>(cmd);

    conexion->enviar((const char*)&cmd,1);
    conexion->enviar((const char*)&type,1);
    conexion->enviar((const char*)&conv_id,4);
    conexion->enviar((const char*)&conv_posx,4);
    conexion->enviar((const char*)&conv_posy,4);
    conexion->enviar((const char*)&conv_angle,4);

//std::cout << angle*100 << "-" << id_obj << "-" << posX << "-" << posY << std::endl;
}

void Protocol::sendWormId(int8_t id, int32_t health) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    int32_t conv_health = htonl(health); 

    Commands cmd = Commands::ATTACH_WORM_ID;

    //char c = static_cast<std::underlying_type<Commands>::type>(cmd);

    conexion->enviar((const char*)&cmd,1);
    conexion->enviar((const char*)&id,1);
    conexion->enviar((const char*)&conv_health,4);    
}

void Protocol::sendUsableId(int8_t id, int32_t ammo) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::ATTACH_USABLE_ID;

    int32_t conv_ammo = htonl(ammo);

    conexion->enviar((const char*)&cmd,1);
    conexion->enviar((const char*)&id,1);
    conexion->enviar((const char*)&conv_ammo,4);       
}

void Protocol::sendPlayerId(int8_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::ATTACH_PLAYER_ID;

    //char c = static_cast<std::underlying_type<Commands>::type>(cmd);

    conexion->enviar((const char*)&cmd,1);
    conexion->enviar((const char*)&id,1);
}

void Protocol::sendRemove(std::string type_obj, int32_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::REMOVE;    
    TypeObj type;

    if (type_obj.compare("Worm")) {
        type = TypeObj::WORM;
    } else if (type_obj.compare("Girder")) {
        type = TypeObj::GIRDER;
    } else if (type_obj.compare("Bazooka")) {
        type = TypeObj::BAZOOKA_M;
    }


    int32_t conv_id = htonl(id); 

    conexion->enviar((const char*)&cmd,1);
    conexion->enviar((const char*)&type,1);
    conexion->enviar((const char*)&conv_id,4);   
}

void Protocol::sendGameEnd() {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::GAME_END;

    conexion->enviar((const char*)&cmd,1);
}

void Protocol::sendActualPlayer(int8_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::ACTUAL_PLAYER;  

    conexion->enviar((const char*)&cmd,1);
    conexion->enviar((const char*)&id,1);
}

void Protocol::sendWinner(int8_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::WINNER;  

    conexion->enviar((const char*)&cmd,1);
    conexion->enviar((const char*)&id,1);
}

void Protocol::recvMove(int* id, int *dir) {
    std::lock_guard<std::mutex> lock(this->server_recv_m);

    conexion->recibir((char*)id,1);
    conexion->recibir((char*)dir,1);
}

void Protocol::recvAttack(int* id_weapon, int* id_worm, int* posx, int* posy, std::vector<float>& params) {
    std::lock_guard<std::mutex> lock(this->server_recv_m);
    
    int8_t uid;
    conexion->recibir((char*)&uid,1);
    *id_weapon = uid;

    conexion->recibir((char*)id_worm,1);

    int32_t aux;

    conexion->recibir((char*)&aux,4);
    *posx = ntohl(aux);
    conexion->recibir((char*)&aux,4);
    *posy = ntohl(aux);

    std::vector<float> extra_params;

    UsableIds usid = static_cast<UsableIds>(uid);

    switch (usid) {
        case UsableIds::BAZOOKA: {
            //Dont receive extra params for now
            break;
        }
    }

    params = std::move(extra_params);
}

//------------------------------------






















// Client

// Client
int convMtToPx(int mt){
    float aux = ((mt*140)/6.0);
    return int(aux + 0.5);
}

int convPxToMt(int px){
    float aux = ((px*6)/140.0);
    return int(aux + 0.5);
}



void Protocol::sendMove(int8_t id_worm,int8_t dir)
{
    //state --> 1 = END     0 = START
    //dir --> 1 = RIGHT     0 = LEFT
    conexion->enviar((const char*)&id_worm,1);
    conexion->enviar((const char*)&dir,1);
}


void Protocol::recvPosition(int8_t *type_obj, int32_t *id_obj, int32_t *posX, int32_t *posY, int32_t *angle)
{
    conexion->recibir((char*)type_obj,1);
    int32_t aux;
    conexion->recibir((char*)&aux,4);
    *id_obj = ntohl(aux);
    conexion->recibir((char*)&aux,4);
    std::cout <<"posX:"<<(ntohl(aux))<<std::endl;
    *posX = convMtToPx(ntohl(aux));
    conexion->recibir((char*)&aux,4);
    std::cout <<"posY:"<<(ntohl(aux))<<std::endl;
    *posY = convMtToPx(ntohl(aux));
    conexion->recibir((char*)&aux,4);
    float aux2=(ntohl(aux)*57.2958/100)+0.5;
    //std::cout << "valor angulo" << aux2 << std::endl;
    int32_t aux3 = (int32_t) aux2;
    *angle = aux3;
}


int8_t Protocol::recvCmd() {
    uint8_t cmd;
    conexion->recibir((char*)&cmd,1);
    return cmd;
}

void Protocol::recvWormId(int8_t *id, int32_t *health)
{
    conexion->recibir((char*)id,1);
    int32_t aux;
    conexion->recibir((char*)&aux,4);
    *health = ntohl(aux);
}

void Protocol::recvPlayerId(int8_t *id)
{
    conexion->recibir((char*)id,1);
}

void Protocol::recvUsableId(int8_t* id,int32_t* ammo)
{
    conexion->recibir((char*)id,1);
    int32_t aux;
    conexion->recibir((char*)&aux,4);
    *ammo= ntohl(aux);
}

void Protocol::recvRemove(int8_t* id_obj,int32_t* id)
{
    conexion->recibir((char*)id_obj,1);
    int32_t aux;
    conexion->recibir((char*)&aux,4);
    *id=ntohl(aux);
}

void Protocol::recvActualPlayer(int8_t* id)
{
    conexion->recibir((char*)id,1);
}


void Protocol::recvWinner(int8_t* id)
{
    conexion->recibir((char*)id,1);
}












void Protocol::sendAttack(int8_t id_weapon, int8_t id_worm, int32_t posX, int32_t posY)
{
    conexion->enviar((const char*)&id_weapon,1);
    conexion->enviar((const char*)&id_worm,1);
    int32_t conv = htonl(posX);
    conexion->enviar((const char*)&conv,4);
    conv = htonl(posY);
    conexion->enviar((const char*)&conv,4);
}

