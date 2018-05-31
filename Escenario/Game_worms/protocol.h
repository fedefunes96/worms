#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "socket.h"
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <mutex>

enum class Commands : uint8_t {
    POSITION = 0,
    ATTACH_WORM_ID,
    ATTACH_USABLE_ID,
    ATTACH_PLAYER_ID,
    REMOVE,
    GAME_END,
    ACTUAL_PLAYER,
    WINNER,
    MOVE,
    ATTACK
};

enum class TypeObj : uint8_t {
    WORM = 0,
    GIRDER = 1,
    BAZOOKA_M = 2
};

enum class UsableIds : uint8_t {
    BAZOOKA = 0
};

class Protocol {
private:
    std::mutex client_send_m;
    std::mutex server_recv_m;
public:
    Protocol(Socket* conexion);
    Protocol(Protocol&&);

    //Server
    void sendPosition(std::string type_obj, int32_t id_obj, float posX, float posY, float angle);
    void sendWormId(int8_t id, int32_t health);
    void sendUsableId(int8_t id, int32_t ammo);
    void sendPlayerId(int8_t id);
    void sendRemove(std::string type_obj, int32_t id);
    void sendGameEnd();
    void sendActualPlayer(int8_t id);
    void sendWinner(int8_t id);
    void recvMove(int* id, int *dir);
    void recvAttack(int* id_weapon, int* id_worm, int* posx, int* posy, std::vector<float>& params);    
    //------------

    void sendMove(int8_t id_worm, int8_t dir);
    void sendJump(int8_t id_worm,int8_t dir);
    void sendAttack(int8_t id_weapon, int8_t id_worm, int32_t posX, int32_t posY);

    void recvPosition(int8_t *type_obj, int32_t *id_obj, int32_t *posX, int32_t *posY, int32_t *angle);
    void recvPlayerId(int8_t *id);

    int8_t recvByte();
    void recvWormId(int8_t *id, int32_t *health);

    int8_t recvCmd();


    void recvMove(int8_t *id, int8_t dir);
private:
    Socket* conexion;

};

#endif // PROTOCOL_H
