#ifndef PROTOCOL_H
#define PROTOCOL_H
#include "socket.h"

class Protocol
{
public:
    Protocol(Socket* conexion);
    void sendMove(int8_t id_worm, int8_t state, int8_t dir);
    void sendJump(int8_t id_worm,int8_t dir);
    void sendAttack(int8_t id_weapon, int8_t id_worm, int32_t posX, int32_t posY);

    void recvObj(int8_t *id,int8_t *vida,int32_t *posX,int32_t *posY,int8_t *angle);
    void recvObj(int8_t *id,int32_t *posX,int32_t *posY,int8_t *angle);
    int8_t recvByte();
    int8_t recvId();

private:
    Socket* conexion;

};

#endif // PROTOCOL_H
