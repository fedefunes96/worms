#include "protocol.h"
#include <iostream>

Protocol::Protocol(Socket& conexion) : conexion(conexion) {}

void Protocol::send_string(const std::string& str) {
    int8_t size = (int8_t) str.size();

    conexion.enviar((const char*)&size, 1); 
    conexion.enviar(str.c_str(), size);
}

void Protocol::send_char(char c) {
	conexion.enviar((const char*)&c, 1); 
}

void Protocol::send_cmd(Commands& cmd) {
    this->send_char(static_cast<char>(cmd));
}

void Protocol::send_type_obj(TypeObj& type) {
    this->send_char(static_cast<char>(type));
}

void Protocol::send_usable(UsableIds& usable) {
    this->send_char(static_cast<char>(usable));
}

void Protocol::send_int_signed(int i) {
    int8_t sign = 1;

    if (i < 0)
        sign = 0;

    int32_t conv = htonl(abs(i));

    conexion.enviar((const char*)&conv, 4);  
    conexion.enviar((const char*)&sign, 1); 
}

void Protocol::send_int_unsigned(unsigned int ui) {
	int32_t conv = htonl(ui);

	conexion.enviar((const char*)&conv, 4);  
}

std::string Protocol::recv_string() {
    int8_t size;

    conexion.recibir((char*)&size, 1);

    char buff[BYTES_RECEIVE+1];
    std::string s;

    while (size > BYTES_RECEIVE) {
        conexion.recibir(buff, BYTES_RECEIVE);
        s.append(buff, BYTES_RECEIVE);
        size -= BYTES_RECEIVE;
    }

    conexion.recibir(buff, size);
    s.append(buff, size); 

    return std::move(s);
}

char Protocol::recv_char() {
	char c;

	conexion.recibir((char*)&c, 1);

	return c;
}

int Protocol::recv_int_signed() {
	int32_t aux;
	int8_t sign;

	conexion.recibir((char*)&aux, 4);
	conexion.recibir((char*)&sign, 1);

	if (!sign)
		sign = -1;

	return ntohl(aux)*sign;	
}

unsigned int Protocol::recv_int_unsigned() {
	int32_t aux;

	conexion.recibir((char*)&aux, 4);

	return ntohl(aux);
}

TypeObj Protocol::recv_type_obj() {
    return static_cast<TypeObj>(this->recv_char());
}

Commands Protocol::recv_cmd() {
    return static_cast<Commands>(this->recv_char());
}

UsableIds Protocol::recv_usable() {
    return static_cast<UsableIds>(this->recv_char());
}
