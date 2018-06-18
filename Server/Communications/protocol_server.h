#ifndef PROTOCOL_SERVER_H
#define PROTOCOL_SERVER_H

#include "socket.h"
#include "protocol.h"
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <mutex>

#define BYTES_RECEIVE 50

class ProtocolServer : public Protocol {
public:
    ProtocolServer(Socket& conexion);

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
};

#endif
