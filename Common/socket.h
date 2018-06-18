#ifndef SOCKETS_H__
#define SOCKETS_H__

#include <string>

#define INVALID_VALUE_SKT -1

class Socket {
private:
	int skt;

	explicit Socket(int skt);
public:
	Socket(const std::string& puerto, const int cant_usuarios);
	Socket(const std::string& ip, const std::string& puerto);

	Socket aceptar();
	void desconectar();
	virtual int recibir(char buff[], const size_t tam_buff);
	virtual void enviar(const char msj[], const size_t tam_msj);
	~Socket();
	Socket(Socket&&);
};

#endif
