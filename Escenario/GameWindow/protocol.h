#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "socket.h"
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <mutex>

#define BYTES_RECEIVE 50

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
    ATTACK,
    SHOW_ROOMS,
    JOIN_ROOM,
    EXIT_ROOM,
    WORM_HEALTH,
    DISCONNECT,
    CREATE_ROOM,
    START_GAME,
    MAP_LIST,
    COULD_JOIN,
    PLAYERS_IN_ROOM,
    WORM_STATUS,
    WIND_PARAMS,
    WIND_SPEED
};

enum class TypeObj : uint8_t {
    WORM = 0,
    GIRDER,
    LARGE_GIRDER,
    SMALL_GIRDER,
    BAZOOKA_M,
    MORTAR_M,
    FRAGMENT_M,
    GREEN_GRENADE_M,
    RED_GRENADE_M,
    BANANA_M,
    HOLY_GRENADE_M,
    DYNAMITE_M,
    AERIAL_ATTACK_M 
};

enum class UsableIds : uint8_t {
    BAZOOKA = 0,
    MORTAR,
    GREEN_GRENADE,
    RED_GRENADE,
    BANANA,
    HOLY_GRENADE,
    DYNAMITE,
    BASEBALL_BAT,
    AERIAL_ATTACK,
    TELEPORTATION
};

class Protocol {
private:
    std::mutex client_send_m;
    std::mutex server_recv_m;
    Socket& conexion;
public:
    Protocol(Socket& conexion);

    //Server
    void sendPosition(const std::string& type_obj, int32_t id_obj, float posX, float posY, float angle);
    void sendActualWorm(int8_t id);
    void sendWormId(int8_t id, int8_t id_worm, int32_t health);
    void sendUsableId(int8_t id, int32_t ammo);
    void sendPlayerId(int8_t id);
    void sendRemove(const std::string& type_obj, int32_t id);
    void sendGameEnd();
    void sendActualPlayer(int8_t id);
    void sendWinner(int8_t id);
    void sendWormHealth(int8_t id, int32_t health);
    void sendDisconnect();
    void sendCouldJoinRoom(int8_t id);
    void sendPlayersInRoom(int8_t size);
    void sendStartGame();
    void sendRooms(const std::vector<std::string>& rooms_name);
    void sendMaps(const std::vector<std::string>&maps);
    void sendWindParams(float min, float max);
    void sendWindSpeed(float speed);
    void recvRoom(std::string& room_name);
    void recvMove(int *dir);
    void recvAttack(int* id_weapon, int* posx, int* posy, std::vector<int>& params);
    void recvCreateRoom(std::string& room_name, std::string& stage_file);
    void sendWormStatus(int8_t id, bool ground, int8_t dir);
    //------------

    void sendMove( int8_t dir);
    void sendJump(int8_t dir);
    void sendAttack(int8_t id_weapon, int32_t posX, int32_t posY, std::vector<int32_t> vect);
    void sendCreateRoom(std::string &name,std::string &stage_file);
    void sendSelectRoom(std::string &name);
    int8_t recvCmd();
    void recvPosition(int8_t *type_obj, int32_t *id_obj, int32_t *posX, int32_t *posY, int32_t *angle);
    void recvPlayerId(int8_t *id);
    void recvWormId(int8_t *id_player, int8_t *id, int32_t *health);
    void recvWinner(int8_t *id);
    void recvActualPlayer(int8_t *id);
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

};

#endif // PROTOCOL_H
