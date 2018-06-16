#include "protocol.h"
#include <iostream>

Protocol::Protocol(Socket& conexion) : conexion(conexion) {}
//Server 
//Server 
void Protocol::sendPosition(const std::string& type_obj, int32_t id_obj, float posX, float posY, float angle) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    TypeObj type;
    Commands cmd = Commands::POSITION;

    if (type_obj.compare("Worm")==0) {
        type = TypeObj::WORM;
    } else if (type_obj.compare("LargeGirder")==0) {
        type = TypeObj::LARGE_GIRDER;
    } else if (type_obj.compare("SmallGirder")==0) {
        type = TypeObj::SMALL_GIRDER;
    } else if (type_obj.compare("Bazooka")==0) {
        type = TypeObj::BAZOOKA_M;
    } else if (type_obj.compare("Mortar")==0) {
        type = TypeObj::MORTAR_M;
    } else if (type_obj.compare("Fragment")==0) {
        type = TypeObj::FRAGMENT_M;
    } else if (type_obj.compare("GreenGrenade")==0) {
        type = TypeObj::GREEN_GRENADE_M;
    } else if (type_obj.compare("RedGrenade")==0) {
        type = TypeObj::RED_GRENADE_M;
    } else if (type_obj.compare("Banana")==0) {
        type = TypeObj::BANANA_M;
    } else if (type_obj.compare("HolyGrenade")==0) {
        type = TypeObj::HOLY_GRENADE_M;
    } else if (type_obj.compare("Dynamite")==0) {
        type = TypeObj::DYNAMITE_M;
    } else if (type_obj.compare("AerialAttack")==0) {
        type = TypeObj::AERIAL_ATTACK_M;
    }

    int8_t posx_sign = 1;
    int8_t posy_sign = 1;
    int8_t angle_sign = 1;

    if (posX < 0)
        posx_sign = 0;
    if (posY < 0)
        posy_sign = 0;
    if (angle_sign < 0)
        angle_sign = 0;

    int32_t conv_id = htonl(id_obj); 
    int32_t conv_posx = htonl((abs(static_cast<int>(posX*10000))));
    int32_t conv_posy = htonl((abs(static_cast<int>(posY*10000))));
    int32_t conv_angle = htonl((abs(static_cast<int>(angle*100))));

    //char c = static_cast<std::underlying_type<Commands>::type>(cmd);

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&type,1);
    conexion.enviar((const char*)&conv_id,4);
    conexion.enviar((const char*)&conv_posx,4);
    conexion.enviar((const char*)&posx_sign,1);
    conexion.enviar((const char*)&conv_posy,4);
    conexion.enviar((const char*)&posy_sign,1);
    conexion.enviar((const char*)&conv_angle,4);
    conexion.enviar((const char*)&angle_sign,1);

    //std::cout << "angulo:" <<angle*100 << "-" << id_obj << "-" << posX << "-" << posY << std::endl;
}

void Protocol::sendActualWorm(int8_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    conexion.enviar((const char*)&id,1);
}

void Protocol::sendWormId(int8_t id, int8_t id_worm, int32_t health) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    int32_t conv_health = htonl(health); 

    Commands cmd = Commands::ATTACH_WORM_ID;

    //char c = static_cast<std::underlying_type<Commands>::type>(cmd);

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id,1);
    conexion.enviar((const char*)&id_worm,1);
    conexion.enviar((const char*)&conv_health,4);    
}

void Protocol::sendWormStatus(int8_t id, bool ground,int8_t dir)
{
    std::lock_guard<std::mutex> lock(this->client_send_m);
    Commands cmd = Commands::WORM_STATUS;
    int8_t on_ground=0;
    if(ground){
        on_ground=1;
    }    
    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id,1);
    conexion.enviar((const char*)&on_ground,1);    
    conexion.enviar((const char*)&dir,1);   
    std::cout << "----> Status idWorm:" << static_cast<int>(id) << " ground:" << static_cast<int>(on_ground) <<  " mDir:" << static_cast<int>(dir) << std::endl;
}

void Protocol::sendUsableId(int8_t id, int32_t ammo) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::ATTACH_USABLE_ID;

    int8_t ammo_sign = 1;

    if (ammo < 0)
        ammo_sign = 0;

    int32_t conv_ammo = htonl(abs(ammo));

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id,1);
    conexion.enviar((const char*)&conv_ammo,4);    
    conexion.enviar((const char*)&ammo_sign,1);   
}

void Protocol::sendPlayerId(int8_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::ATTACH_PLAYER_ID;

    //char c = static_cast<std::underlying_type<Commands>::type>(cmd);

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id,1);
}

void Protocol::sendRemove(const std::string& type_obj, int32_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::REMOVE;    
    TypeObj type;

    if (type_obj.compare("Worm")==0) {
        type = TypeObj::WORM;
    } else if (type_obj.compare("LargeGirder")==0) {
        type = TypeObj::LARGE_GIRDER;
    } else if (type_obj.compare("SmallGirder")==0) {
        type = TypeObj::SMALL_GIRDER;
    } else if (type_obj.compare("Bazooka")==0) {
        type = TypeObj::BAZOOKA_M;
    } else if (type_obj.compare("Mortar")==0) {
        type = TypeObj::MORTAR_M;
    } else if (type_obj.compare("Fragment")==0) {
        type = TypeObj::FRAGMENT_M;
    } else if (type_obj.compare("GreenGrenade")==0) {
        type = TypeObj::GREEN_GRENADE_M;
    } else if (type_obj.compare("RedGrenade")==0) {
        type = TypeObj::RED_GRENADE_M;
    } else if (type_obj.compare("Banana")==0) {
        type = TypeObj::BANANA_M;
    } else if (type_obj.compare("HolyGrenade")==0) {
        type = TypeObj::HOLY_GRENADE_M;
    } else if (type_obj.compare("Dynamite")==0) {
        type = TypeObj::DYNAMITE_M;
    } else if (type_obj.compare("AerialAttack")==0) {
        type = TypeObj::AERIAL_ATTACK_M;
    }

    int32_t conv_id = htonl(id); 

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&type,1);
    conexion.enviar((const char*)&conv_id,4);   
}

void Protocol::sendGameEnd() {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::GAME_END;

    conexion.enviar((const char*)&cmd,1);
}

void Protocol::sendActualPlayer(int8_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::ACTUAL_PLAYER;  

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id,1);
}

void Protocol::sendWinner(int8_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::WINNER;  

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id,1);
}

void Protocol::sendWormHealth(int8_t id, int32_t health) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::WORM_HEALTH;  

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id,1);

    int32_t conv_h = htonl(health);

    conexion.enviar((const char*)&conv_h,4); 
}

void Protocol::sendDisconnect() {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::DISCONNECT;  

    conexion.enviar((const char*)&cmd,1);    
}

void Protocol::sendCouldJoinRoom(int8_t id) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::COULD_JOIN;  

    conexion.enviar((const char*)&cmd,1); 
    conexion.enviar((const char*)&id,1);      
}

void Protocol::sendPlayersInRoom(int8_t size) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::PLAYERS_IN_ROOM;  

    conexion.enviar((const char*)&cmd,1); 
    conexion.enviar((const char*)&size,1);  
}

void Protocol::sendStartGame() {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::START_GAME;  

    conexion.enviar((const char*)&cmd,1); 
}

void Protocol::sendWindParams(float min, float max) {
    int32_t conv_min = htonl((abs(static_cast<int>(min*100))));
    int32_t conv_max = htonl((abs(static_cast<int>(max*100))));

    Commands cmd = Commands::WIND_PARAMS; 

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&conv_min,4);
    conexion.enviar((const char*)&conv_max,4);
}

void Protocol::sendWindSpeed(float speed) {
    int32_t conv = htonl((abs(static_cast<int>(speed*100))));

    Commands cmd = Commands::WIND_SPEED; 

    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&conv,4);
}

void Protocol::sendRooms(const std::vector<std::string>& rooms_name) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::SHOW_ROOMS;  

    int8_t size = (int8_t) rooms_name.size();

    conexion.enviar((const char*)&cmd,1); 
    conexion.enviar((const char*)&size,1); 

    for (int i = 0; i < (int) rooms_name.size(); i++) {
        size = (int8_t) rooms_name[i].size();

        conexion.enviar((const char*)&size,1); 
        conexion.enviar(rooms_name[i].c_str(), size);
    }
}

void Protocol::sendMaps(const std::vector<std::string>&maps) {
    std::lock_guard<std::mutex> lock(this->client_send_m);

    Commands cmd = Commands::MAP_LIST;

    int8_t size = (int8_t) maps.size();

    conexion.enviar((const char*)&cmd,1); 
    conexion.enviar((const char*)&size,1); 

    for (int i = 0; i < (int) maps.size(); i++) {
        size = (int8_t) maps[i].size();
        printf("%s\n",maps[i].c_str());
        conexion.enviar((const char*)&size,1); 
        conexion.enviar(maps[i].c_str(), size);
    }   
}

void Protocol::recvRoom(std::string& room_name) {
    std::lock_guard<std::mutex> lock(this->server_recv_m);

    int8_t size;

    conexion.recibir((char*)&size,1);

    char buff[BYTES_RECEIVE+1];

    while (size > BYTES_RECEIVE) {
        conexion.recibir(buff, BYTES_RECEIVE);
        room_name.append(buff, BYTES_RECEIVE);
        size -= BYTES_RECEIVE;
    }

    conexion.recibir(buff, size);
    room_name.append(buff, size);   
}

void Protocol::recvCreateRoom(std::string& room_name, std::string& stage_file) {
    std::lock_guard<std::mutex> lock(this->server_recv_m);    

    int8_t size;

    conexion.recibir((char*)&size,1);

    char buff[BYTES_RECEIVE+1];

    while (size > BYTES_RECEIVE) {
        conexion.recibir(buff, BYTES_RECEIVE);
        room_name.append(buff, BYTES_RECEIVE);
        size -= BYTES_RECEIVE;
    }

    conexion.recibir(buff, size);
    room_name.append(buff, size);  

    conexion.recibir((char*)&size,1);
    char buff2[BYTES_RECEIVE+1];

    while (size > BYTES_RECEIVE) {
        conexion.recibir(buff2, BYTES_RECEIVE);
        stage_file.append(buff2, BYTES_RECEIVE);
        size -= BYTES_RECEIVE;
    }

    conexion.recibir(buff2, size);
    stage_file.append(buff2, size);          
}

void Protocol::recvMove(int *dir) {
    std::lock_guard<std::mutex> lock(this->server_recv_m);

    conexion.recibir((char*)dir,1);
}

void Protocol::recvAttack(int* id_weapon, int* posx, int* posy, std::vector<int>& params) {
    std::lock_guard<std::mutex> lock(this->server_recv_m);
    
    int8_t uid;
    conexion.recibir((char*)&uid,1);
    *id_weapon = uid;

    int32_t aux;

    conexion.recibir((char*)&aux,4);
    *posx = ntohl(aux);
    conexion.recibir((char*)&aux,4);
    *posy = ntohl(aux);

    UsableIds usid = static_cast<UsableIds>(uid);

    switch (usid) {
        case UsableIds::BAZOOKA: {
            conexion.recibir((char*)&aux,4);
            int32_t aux2 = ntohl(aux);
            params.push_back(aux2);
            break;
        }
        case UsableIds::MORTAR: {
            conexion.recibir((char*)&aux,4);
            params.push_back(ntohl(aux));
            break;
        }  
        case UsableIds::GREEN_GRENADE: {
            conexion.recibir((char*)&aux,4);
            params.push_back((ntohl(aux)));
            conexion.recibir((char*)&aux,4);
            params.push_back((ntohl(aux)));            
            break;
        }   
        case UsableIds::RED_GRENADE: {
            conexion.recibir((char*)&aux,4);
            params.push_back((ntohl(aux)));
            conexion.recibir((char*)&aux,4);
            params.push_back((ntohl(aux)));            
            break;
        }   
         case UsableIds::BANANA: {
            conexion.recibir((char*)&aux,4);
            params.push_back((ntohl(aux)));
            conexion.recibir((char*)&aux,4);
            params.push_back((ntohl(aux)));           
            break;
        }   
        case UsableIds::HOLY_GRENADE: {
            conexion.recibir((char*)&aux,4);
            params.push_back((ntohl(aux)));
            conexion.recibir((char*)&aux,4);
            params.push_back((ntohl(aux)));            
            break;
        } 
        case UsableIds::DYNAMITE: {
            conexion.recibir((char*)&aux,4);
            params.push_back((ntohl(aux)));            
            break;
        }     
        default: break;                                          
    }
}


//------------------------------------













// Client

// Client
int convMtToPx(float mt){
    float aux = ((mt*140)/6.0);
    return int(aux + 0.5);
}

int convPxToMt(int px){
    float aux = ((px*6)/140.0);
    //std::cout << "conver MT:" << (aux) << std::endl;
    return int(aux + 0.5);
}

void Protocol::sendMove(int8_t dir)
{
    //state --> 1 = END     0 = START
    //dir --> 1 = RIGHT     0 = LEFT

    Commands cmd = Commands::MOVE;
    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&dir,1);
    //std::cout << "en protocolo envio movimiento:"<<static_cast<int>(cmd)<<"en direccion:"<<static_cast<int>(dir)<<std::endl;
}


void Protocol::recvPosition(int8_t *type_obj, int32_t *id_obj, int32_t *posX, int32_t *posY, int32_t *angle) {
    int32_t aux;
    int8_t sign;
    int mult;

    conexion.recibir((char*)type_obj,1);
    conexion.recibir((char*)&aux,4);
    *id_obj = ntohl(aux);
    conexion.recibir((char*)&aux,4);
    conexion.recibir((char*)&sign,1);

    mult = (sign == 1) ? 1 : -1;

    *posX = convMtToPx(ntohl(aux)*mult/10000.0);

    conexion.recibir((char*)&aux,4);
    conexion.recibir((char*)&sign,1);

    mult = (sign == 1) ? 1 : -1;
    *posY = convMtToPx(ntohl(aux)*mult/10000.0);

    conexion.recibir((char*)&aux,4);
    conexion.recibir((char*)&sign,1);

    mult = (sign == 1) ? 1 : -1;
    float aux2=(ntohl(aux)*mult*57.2958/100)+0.5;
    int32_t aux3 = (int32_t) aux2;
    *angle = aux3;

}


void Protocol::recvWormStatus(int8_t *id, int8_t *ground,int8_t *dir)
{
    conexion.recibir((char*)id,1);
    conexion.recibir((char*)ground,1);
    conexion.recibir((char*)dir,1);
    std::cout << "worm id:" << static_cast<int>(*id) << "on_ground:" << static_cast<int>(*ground) << "dir:" << static_cast<int>(*dir) << std::endl;
    //si toco el enter o el de saltar atras muy rapido el server manda directamente el 0 y nunca el 3 o 4...
}



int8_t Protocol::recvCmd() {
    uint8_t cmd;
    conexion.recibir((char*)&cmd,1);
    //std::cout << "command:" << static_cast<int16_t>(cmd) << std::endl;
    return cmd;
}

void Protocol::recvWormId(int8_t* id_player,int8_t *id, int32_t *health)
{
    conexion.recibir((char*)id_player,1);
    conexion.recibir((char*)id,1);
    int32_t aux;
    conexion.recibir((char*)&aux,4);
    *health = ntohl(aux);
    //std::cout << "idWorm:" << static_cast<int16_t>(*id) << "health:" << *health << std::endl;
}

void Protocol::recvPlayerId(int8_t *id)
{
    conexion.recibir((char*)id,1);
    //std::cout << "idPlayer:" << static_cast<int16_t>(*id) << std::endl;
}

void Protocol::recvUsableId(int8_t* id,int32_t* ammo)
{
    conexion.recibir((char*)id,1);
    int32_t aux;
    int8_t sign;
    int mult;
    conexion.recibir((char*)&aux,4);
    conexion.recibir((char*)&sign,1);

    mult = (sign == 1) ? 1 : -1;

    *ammo= ntohl(aux)*mult;
}

void Protocol::recvRemove(int8_t* id_obj,int32_t* id)
{
    conexion.recibir((char*)id_obj,1);
    int32_t aux;
    conexion.recibir((char*)&aux,4);
    *id=ntohl(aux);
}


void Protocol::recvWindParamt(int32_t* min, int32_t* max)
{
    int32_t aux;
    conexion.recibir((char*)&aux,4);
    *min = ntohl(aux);
    conexion.recibir((char*)&aux,4);
    *max = ntohl(aux);
}

void Protocol::recvWindSpeed(int32_t* speed)
{
    int32_t aux;
    conexion.recibir((char*)&aux,4);
    *speed = ntohl(aux);
}


void Protocol::recvActualPlayer(int8_t* id, int8_t* id_worm)
{
    conexion.recibir((char*)id,1);
    conexion.recibir((char*)id_worm,1);
}

void Protocol::recvActualWorm(int8_t *id){
    conexion.recibir((char*)id,1);
}


void Protocol::recvWinner(int8_t* id)
{
    conexion.recibir((char*)id,1);
}


void Protocol::sendAttack(int8_t id_weapon, int32_t posX, int32_t posY, std::vector<int32_t> vect)
{
    Commands cmd = Commands::ATTACK;
    conexion.enviar((const char*)&cmd,1);
    conexion.enviar((const char*)&id_weapon,1);
    int32_t conv = htonl(convPxToMt(posX));
    conexion.enviar((const char*)&conv,4);
    conv = htonl(convPxToMt(posY));
    conexion.enviar((const char*)&conv,4);

    for (unsigned int var = 0; var < vect.size(); ++var) {
        int32_t aux = htonl(vect[var]);
        conexion.enviar((const char*)&aux,4);
        //std::cout << "dentro del vector hay:" << vect[var] <<std::endl;
    }
    //std::cout << "idweapon:" << static_cast<int16_t>(id_weapon) << "posX:"<<posX <<"posY:"<<posY << std::endl;

}

void Protocol::sendCreateRoom(std::string &name, std::string &stage_file)
{
    Commands cmd = Commands::CREATE_ROOM;
    printf("%s\n", stage_file.c_str());
    printf("%s\n", name.c_str());
    conexion.enviar((const char*)&cmd,1);
    char tam = name.size();
    conexion.enviar((const char*)&tam,1);
    conexion.enviar(name.c_str(),name.size());
    tam = stage_file.size();
    conexion.enviar((const char*)&tam,1);
    conexion.enviar(stage_file.c_str(),stage_file.size());
}

void Protocol::sendSelectRoom(std::string &name)
{
    Commands cmd = Commands::JOIN_ROOM;
    conexion.enviar((const char*)&cmd,1);
    char tam = name.size();
    conexion.enviar((const char*)&tam,1);
    conexion.enviar(name.c_str(),name.size());
}


void Protocol::recvWormHealth(int8_t *id, int32_t *health) {
    conexion.recibir((char*)id,1);
    int32_t aux;
    conexion.recibir((char*)&aux,4);
    *health = ntohl(aux);
}


int8_t Protocol::recvCouldJoinRoom(){
    int8_t conecto;
    conexion.recibir((char*)&conecto,1);
    return conecto;
}

int8_t Protocol::recvPlayersInRoom(){
    int8_t cant;
    conexion.recibir((char*)&cant,1);
    return cant;
}

void Protocol::recvRomms(std::vector<std::string>& rooms_name){
    int8_t size;
    conexion.recibir((char*)&size,1);
    for (int i = 0; i <(int8_t) size; ++i)
    {
        char buff[BYTES_RECEIVE+1];
        int8_t tam;
        conexion.recibir((char*)&tam,1);
        std::string name;
        while (tam > BYTES_RECEIVE){
            conexion.recibir(buff,BYTES_RECEIVE);
            name.append(buff,BYTES_RECEIVE);
            tam -= BYTES_RECEIVE;
        }
        conexion.recibir(buff,tam);
        name.append(buff,tam);
        std::cout << "nombre recibido" << name << std::endl;
        rooms_name.push_back(name);
    }
}

void Protocol::recvMaps(std::vector<std::string>& rooms_name){
    int8_t size;
    conexion.recibir((char*)&size,1);
    for (int i = 0; i <(int8_t) size; ++i)
    {
        char buff[BYTES_RECEIVE+1];
        int8_t tam;
        conexion.recibir((char*)&tam,1);
        std::string name;
        while (tam > BYTES_RECEIVE){
            conexion.recibir(buff,BYTES_RECEIVE);
            name.append(buff,BYTES_RECEIVE);
            tam -= BYTES_RECEIVE;
        }
        conexion.recibir(buff,tam);
        name.append(buff,tam);
        std::cout << "nombre "<<name << std::endl;
        rooms_name.push_back(name);
    }
}

void Protocol::sendJoinRoom()
{
   Commands cmd = Commands::SHOW_ROOMS;
   conexion.enviar((const char*)&cmd,1);
}

void Protocol::sendCreateRoom()
{
    Commands cmd = Commands::MAP_LIST;
    conexion.enviar((const char*)&cmd,1);
}

void Protocol::sendExitRoom()
{
    Commands cmd = Commands::EXIT_ROOM;
    conexion.enviar((const char*)&cmd,1);
}



