#include "protocol.h"
#include <iostream>
Protocol::Protocol(Socket *conexion):conexion(conexion)
{
}

//Server 
void Protocol::sendPosition(int8_t type_obj, int32_t id_obj, int32_t posX, int32_t posY, int32_t angle) {
    int32_t conv_id = htonl(id_obj); 
    int32_t conv_posx = htonl(posX);
    int32_t conv_posy = htonl(posY);
    int32_t conv_angle = htonl(angle*100);

    conexion->enviar((const char*)&type_obj,1);
    conexion->enviar((const char*)&conv_id,4);
    conexion->enviar((const char*)&conv_posx,4);
    conexion->enviar((const char*)&conv_posy,4);
    conexion->enviar((const char*)&conv_angle,4);

//std::cout << angle*100 << "-" << id_obj << "-" << posX << "-" << posY << std::endl;
}

void Protocol::sendWormId(int8_t id, int32_t health) {
    int32_t conv_health = htonl(health); 

    conexion->enviar((const char*)&id,1);
    conexion->enviar((const char*)&conv_health,4);    
}

void Protocol::sendPlayerId(int8_t id) {
    conexion->enviar((const char*)&id,1);
}

void Protocol::recvMove(int8_t* id, int8_t *dir){
    conexion->recibir((char*)id,1);
    conexion->recibir((char*)dir,1);
}

//------------------------------------


void Protocol::sendMove(int8_t id_worm,int8_t dir)
{
    //state --> 1 = END     0 = START
    //dir --> 1 = RIGHT     0 = LEFT
    conexion->enviar((const char*)&id_worm,1);
    conexion->enviar((const char*)&dir,1);
}

void Protocol::sendJump(int8_t id_worm, int8_t dir)
{
    conexion->enviar((const char*)&id_worm,1);
    conexion->enviar((const char*)&dir,1);
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



void Protocol::recvPosition(int8_t *type_obj, int32_t *id_obj, int32_t *posX, int32_t *posY, int32_t *angle)
{
    conexion->recibir((char*)type_obj,1);
    int32_t aux;
    conexion->recibir((char*)&aux,4);
    *id_obj = ntohl(aux);
    conexion->recibir((char*)&aux,4);
    *posX = ntohl(aux);
    conexion->recibir((char*)&aux,4);
//    printf("%d\n", ntohl(aux));
    *posY = ntohl(aux);
    conexion->recibir((char*)&aux,4);
    float aux2=(ntohl(aux)*57.325/100.0);
    int32_t aux3 = (int32_t) aux2;
    *angle = aux3;


//    std::cout << *id_obj << "-" << *posX << "-" << *posY << std::endl;
}

int8_t Protocol::recvCmd()
{
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

