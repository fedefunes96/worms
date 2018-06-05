#define _POSIX_C_SOURCE 200112L

#include "socket.h"
#include <string>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include "common_socket_exception.h"

Socket::Socket(int skt) {
	this->skt = skt;
}

Socket::Socket(const std::string& puerto, const int cant_usuarios) {
	struct addrinfo hints;
	struct addrinfo *ptr, *res;

	bool enlazado = false;
	int skt = 0;
	int s = 0;
	int val;

	memset(&hints, 0, sizeof(struct addrinfo));	
	hints.ai_family = AF_INET;       
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = AI_PASSIVE;	
	
	// Obtenemos las direcciones posibles
	s = getaddrinfo(NULL, puerto.c_str(), &hints, &ptr);

	if (s != 0) { 
		throw SocketException("No se pudo realizar getaddrinfo al enlazar socket");
	}

	for (res = ptr; res != NULL; res = res->ai_next) {
		//Creamos el socket con las especificaciones dadas
      	skt = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

		if (skt == -1)
			continue;
		//Establecemos las opciones del socket
		val = 1;
		s = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

		if (s == -1) {
			close(skt);
			continue;
		}		
		//Enlazamos el socket a la direccion local obtenida
		s = bind(skt, res->ai_addr, res->ai_addrlen);	
			
		if (s == -1) {
			close(skt);
			continue;
		}
		//Establecemos la cantidad de clientes 
		//que pueden haber en espera antes de aceptarlos
	  	s = listen(skt, cant_usuarios);

		if (s == -1) {
			close(skt);
			continue;
		}		
		//Nos pudimos enlazar, no necesitamos chequear más
		enlazado = true;
		break;	
	}
	//Liberamos la lista de direcciones locales
	freeaddrinfo(ptr); 

	//No se pudo enlazar a ninguna direccion
	if (!enlazado) {
		throw SocketException("No se pudo enlazar el socket");;
	}

	this->skt = skt;
	//return 1;	
}

Socket::Socket(const std::string& ip, const std::string& puerto) {
	struct addrinfo hints;
	struct addrinfo *ptr, *res;

	bool conectado = false;
	int skt = 0;
	int s = 0;

	memset(&hints, 0, sizeof(struct addrinfo));	
	hints.ai_family = AF_INET;       
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = AI_PASSIVE;	
	
	// Obtenemos las direcciones posibles
	s = getaddrinfo(ip.c_str(), puerto.c_str(), &hints, &ptr);

	if (s != 0) { 
		throw SocketException("No se pudo realizar getaddrinfo al conectar socket");
	}

	for (res = ptr; res != NULL; res = res->ai_next) {
		//Creamos el socket con las especificaciones dadas
      	skt = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

		if (skt == -1)
			continue;
		
		//Conectamos el socket a la direccion obtenida
		s = connect(skt, res->ai_addr, res->ai_addrlen);	

		if (s == -1) {
			close(skt);
			continue;
		}
		
		//Nos pudimos conectar, no necesitamos chequear más
		conectado = true;
		break;	
	}
	//Liberamos la lista de direcciones
	freeaddrinfo(ptr); 

	//No se pudo conectar a ninguna direccion
	if (!conectado) {
		throw SocketException("No se pudo conectar el socket");
	}

	this->skt = skt;	
}

Socket Socket::aceptar() {
	int peerskt = accept(this->skt, NULL, NULL);

	//No se pudo aceptar al usuario
	if (peerskt == -1) {
		throw SocketException("No se pudo aceptar el usuario");
	}	

	return std::move(Socket(peerskt));
}

void Socket::desconectar() {
	shutdown(this->skt, SHUT_RDWR);
}

int Socket::recibir(char buff[], const size_t tam_buff) {
	memset(buff, 0, tam_buff);
	
	int recibidos = 0;
	int s = 0;

	while ((unsigned int) recibidos < tam_buff) {
		s = recv(this->skt, &buff[recibidos], tam_buff-recibidos, MSG_NOSIGNAL);

		if (s == -1) {
			throw SocketException("Error al recibir un mensaje");
		} else if (s == 0) {
			//Se cerro la conexion, devuelvo lo que 
			//recibi hasta el momento y dejo de recibir
			//return recibidos;
			throw SocketException("Error al recibir un mensaje");
		}

		recibidos += s;
	}

	return recibidos;	
}

void Socket::enviar(const char msj[], const size_t tam_msj) {
	int enviados = 0;
	int s = 0;

	while ((unsigned int) enviados < tam_msj) {
		s = send(this->skt, &msj[enviados], tam_msj-enviados, MSG_NOSIGNAL);

		if (s == -1) {
			throw SocketException("Error al enviar un mensaje");
		} else if (s == 0) {
			//Se cerro la conexion o enviamos menos bytes de lo esperado en total
			//No lo proceso, el usuario debe de encargarse 
			//de saber cuanto enviar en total
			throw SocketException("Error al enviar un mensaje");
		}

		enviados += s;
	}	
}

Socket::~Socket() {
	this->desconectar();
	close(this->skt);
}

Socket::Socket(Socket&& other) {
	this->skt = other.skt;
	other.skt = 0;
}
