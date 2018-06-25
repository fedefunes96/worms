#ifndef PROTOCOL_CLIENT_H
#define PROTOCOL_CLIENT_H

#include "socket.h"
#include "protocol.h"
#include <arpa/inet.h>
#include <string>
#include <vector>

#define BYTES_RECEIVE 50

class ProtocolClient : public Protocol {
public:
    ProtocolClient(Socket& conexion);
    void sendMove( int8_t dir);
    void sendAttack(int8_t id_weapon, int32_t posX, int32_t posY, std::vector<int32_t> vect);
    void sendCreateRoom(std::string &name,std::string &stage_file);
    void sendSelectRoom(std::string &name);
    int8_t recvCmd();
    void recvPosition(int8_t *type_obj, int32_t *id_obj, int32_t *posX,
                      int32_t *posY, int32_t *angle);
    void recvPlayerId(int8_t *id);
    void recvWormId(int8_t *id_player, int8_t *id, int32_t *health);
    void recvWinner(int8_t *id);
    void recvActualPlayer(int8_t* id, int8_t* id_worm);
    void recvRemove(int8_t *id_obj, int32_t *id);
    void recvUsableId(int8_t *id, int32_t *ammo);
    void recvWormHealth(int8_t *id, int32_t *health);
    int8_t recvCouldJoinRoom();
    int8_t recvPlayersInRoom();
    void recvRomms(std::vector<std::string>& rooms_name);
    void recvMaps(std::vector<std::string>& rooms_name);
    void sendJoinRoom();
    void sendCreateRoom();
    void sendExitRoom();
    void recvActualWorm(int8_t *id);
    void recvWormStatus(int8_t *id, int8_t *ground,int8_t *dir);
    void recvWindParamt(int32_t *min, int32_t *max);
    void recvWindSpeed(int32_t *speed);
    std::string recvBackground();
};

#endif
