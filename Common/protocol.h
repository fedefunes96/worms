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
    Socket& conexion;
public:
    Protocol(Socket& conexion);

    void send_string(const std::string& str);
    void send_char(char c);
    void send_cmd(Commands& cmd);
    void send_type_obj(TypeObj& type);
    void send_usable(UsableIds& usable);
    void send_int_signed(int i);
    void send_int_unsigned(unsigned int ui);

    std::string recv_string();
    char recv_char();
    TypeObj recv_type_obj();
    Commands recv_cmd();
    UsableIds recv_usable();
    int recv_int_signed();
    unsigned int recv_int_unsigned();
};

#endif
