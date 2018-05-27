#include "protocol.h"

#include <arpa/inet.h>


Protocol::Protocol(Socket *conexion):conexion(conexion)
{
}




void Protocol::sendMove(int8_t id_worm,int8_t state,int8_t dir)
{
    conexion->enviar((const char*)&id_worm,1);
    conexion->enviar((const char*)&state,1);
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







void Protocol::recvObj(int8_t *id, int8_t *vida, int32_t *posX, int32_t *posY, int8_t *angle)
{
    int32_t aux;
    conexion->recibir((char*)id,1);
    conexion->recibir((char*)vida,1);
    conexion->recibir((char*)&aux,4);
    *posX = ntohl(aux);
    conexion->recibir((char*)&aux,4);
    *posY = ntohl(aux);
    conexion->recibir((char*)angle,1);
}
void Protocol::recvObj(int8_t *id,int32_t *posX, int32_t *posY, int8_t *angle)
{
    int32_t aux;
    conexion->recibir((char*)id,1);
    conexion->recibir((char*)&aux,4);
    *posX = ntohl(aux);
    conexion->recibir((char*)&aux,4);
    *posY = ntohl(aux);
    conexion->recibir((char*)angle,1);
}

int8_t Protocol::recvCmd()
{
    uint8_t cmd;
    conexion->recibir((char*)&cmd,1);
    return cmd;
}

int8_t Protocol::recvId()
{
    uint8_t id;
    conexion->recibir((char*)&id,1);
    return id;
}



