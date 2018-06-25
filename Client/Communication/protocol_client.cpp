#include "socket.h"
#include "protocol.h"
#include "protocol_client.h"
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <iostream>

ProtocolClient::ProtocolClient(Socket& conexion) : Protocol(conexion) {}

int convMtToPx(float mt){
    float aux = ((mt*140)/6.0);
    return int(aux + 0.5);
}

int convPxToMt(int px){
    float aux = ((px*6)/140.0);
    //std::cout << "conver MT:" << (aux) << std::endl;
    return int(aux + 0.5);
}

void ProtocolClient::sendMove(int8_t dir)
{
    Commands cmd = Commands::MOVE;
    this->send_cmd(cmd);
    this->send_char(dir);
}

void ProtocolClient::sendAttack(int8_t id_weapon, int32_t posX,
                                int32_t posY, std::vector<int32_t> vect)
{
    Commands cmd = Commands::ATTACK;
    this->send_cmd(cmd);
    this->send_char(id_weapon);
    this->send_int_unsigned(convPxToMt(posX));
    this->send_int_unsigned(convPxToMt(posY));

    for (unsigned int var = 0; var < vect.size(); ++var) {
        this->send_int_unsigned(vect[var]);
    }
}


void ProtocolClient::sendCreateRoom(std::string &name,std::string &stage_file)
{
    Commands cmd = Commands::CREATE_ROOM;
    this->send_cmd(cmd);
    this->send_string(name);
    this->send_string(stage_file);
}



void ProtocolClient::sendSelectRoom(std::string &name)
{
    Commands cmd = Commands::JOIN_ROOM;
    this->send_cmd(cmd);
    this->send_string(name);
}



int8_t ProtocolClient::recvCmd()
{
    return (int8_t) (this->recv_cmd());
}



void ProtocolClient::recvPosition(int8_t *type_obj,
                                  int32_t *id_obj,
                                  int32_t *posX,
                                  int32_t *posY,
                                  int32_t *angle)
{
    *type_obj = this->recv_char();
    *id_obj = this->recv_int_unsigned();
    *posX = convMtToPx((this->recv_int_signed())/10000.0);
    *posY = convMtToPx((this->recv_int_signed())/10000.0);
    *angle = (this->recv_int_signed()*57.2958/100)+0.5;
}







void ProtocolClient::recvPlayerId(int8_t *id)
{
    *id = this->recv_char();
}


void ProtocolClient::recvWormId(int8_t *id_player, int8_t *id, int32_t *health)
{
    *id_player = this->recv_char();
    *id = this->recv_char();
    *health = this->recv_int_unsigned();    
}



void ProtocolClient::recvWinner(int8_t *id)
{
    *id = this->recv_char();
}


void ProtocolClient::recvActualPlayer(int8_t* id, int8_t* id_worm)
{
    *id = this->recv_char();
    *id_worm = this->recv_char();
}




void ProtocolClient::recvRemove(int8_t *id_obj, int32_t *id)
{
    *id_obj = this->recv_char();
    *id = this->recv_int_unsigned();
}


void ProtocolClient::recvUsableId(int8_t *id, int32_t *ammo)
{
    *id = this->recv_char();
    *ammo = this->recv_int_signed();
}




void ProtocolClient::recvWormHealth(int8_t *id, int32_t *health)
{
    *id = this->recv_char();
    *health = this->recv_int_unsigned();
}

int8_t ProtocolClient::recvCouldJoinRoom()
{
    return this->recv_char();
}

int8_t ProtocolClient::recvPlayersInRoom()
{
    return this->recv_char();
}

void ProtocolClient::recvRomms(std::vector<std::string>& rooms_name)
{
    int8_t size = this->recv_char();
    for (int i = 0; i < size; ++i)
    {
        rooms_name.push_back(this->recv_string());
    }
}




void ProtocolClient::recvMaps(std::vector<std::string>& rooms_name)
{
    int8_t size = this->recv_char();
    for (int i = 0; i < size; ++i)
    {
        rooms_name.push_back(this->recv_string());
    }
}



void ProtocolClient::sendJoinRoom()
{
    Commands cmd = Commands::SHOW_ROOMS;
    this->send_cmd(cmd);
}


void ProtocolClient::sendCreateRoom()
{
    Commands cmd = Commands::MAP_LIST;
    this->send_cmd(cmd);
}


void ProtocolClient::sendExitRoom()
{
    Commands cmd = Commands::EXIT_ROOM;
    this->send_cmd(cmd);
}


void ProtocolClient::recvActualWorm(int8_t *id)
{
    *id = this->recv_char();
}

void ProtocolClient::recvWormStatus(int8_t *id, int8_t *ground,int8_t *dir)
{
    *id = this->recv_char();
    *ground = this->recv_char();
    *dir = this->recv_char();
}


void ProtocolClient::recvWindParamt(int32_t *min, int32_t *max)
{    
    *min = this->recv_int_unsigned();
    *max = this->recv_int_unsigned();
}


void ProtocolClient::recvWindSpeed(int32_t *speed)
{
    *speed = this->recv_int_signed();
}

std::string ProtocolClient::recvBackground()
{
    return this->recv_string();
}