#define _POSIX_C_SOURCE 200112L
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <netinet/ip.h> 
#include "socket.h"
#define INVALID -1
#define CERO 0


//Definicion del constructor
Socket::Socket(const std::string& ip, const std::string& puerto){
	server=false;
	this->skt=CERO;
	this->fd=CERO;
	struct addrinfo hints;
	struct addrinfo *temp, *ptr;	
	const char* ip_c = ip.c_str();
	const char* puerto_c = puerto.c_str();
	memset(&hints,CERO,sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = CERO;
	int skt;
	this->fd = getaddrinfo(ip_c,puerto_c,&hints,&ptr);
	if (this->fd!= CERO){
		return; 
	}
	bool skt_cnect = false;
	for(temp=ptr; (temp!=NULL)&&(skt_cnect==false); temp=temp->ai_next){
		skt=socket(temp->ai_family,temp->ai_socktype,temp->ai_protocol);
		if(skt == INVALID){
			printf("Error: %s\n", strerror(errno));
		}else{
			this->fd =connect(skt,temp->ai_addr,temp->ai_addrlen);
			if(this->fd == INVALID){
				close(skt);
			}
			skt_cnect = (this->fd != INVALID);
		}
	}
	freeaddrinfo(ptr);
	if (skt_cnect==false){
		throw std::runtime_error("Error conexion Socket al crear.\n");
		return;
	}
	this->skt=skt;
}

Socket::Socket(){
	this->skt=CERO;
	this->fd=CERO;
}

Socket::Socket(const std::string& puerto){
	server=true;
	skt=CERO;
	fd=CERO;
	const char* puerto_c = puerto.c_str();
	struct addrinfo hints;
	struct addrinfo *ptr;	

	memset(&hints,CERO,sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	int skt2;
	fd = getaddrinfo("0",puerto_c,&hints,&ptr);
	if (fd!= CERO){
		printf("Error: %s\n", gai_strerror(fd));
		return;
	}
	skt2=socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
	if(skt2==INVALID){
		printf("Error: %s\n", strerror(errno));
		freeaddrinfo(ptr);
		return;
	}
	fd = bind(skt2,ptr->ai_addr,ptr->ai_addrlen);
	if(fd==INVALID){
		printf("Error: %s\n", strerror(errno));
		close(skt2);
		freeaddrinfo(ptr);
		return;
	}
	freeaddrinfo(ptr);
	fd = listen(skt2,1);
	if(fd==INVALID){
		printf("Error: %s\n", strerror(errno));
		close(skt2);
		return;
	}
	skt=skt2;
}

Socket* Socket::server_aceptar_clt(){
	if(!server){
		return nullptr;
	}
	int skt_nuevo = accept(skt,NULL,NULL);
	if(skt_nuevo==INVALID){
		return nullptr;
	}
	Socket* socket_n = new Socket();
	socket_n->set_skt(skt_nuevo);
	return socket_n;
}


void Socket::set_skt(int skt){
	this->skt=skt;
}
void Socket::set_fd(int fd){
	this->fd=fd;
}


Socket::Socket(Socket&& other){
	this->skt = other.skt;
	this->fd = other.fd;
	other.skt = CERO;
	other.fd = CERO;
}



int Socket::enviar(const char* texto, int cantidad){
	int bytes_enviar = cantidad;
	int b_env = CERO;
	int bytes_exito;
	bool socket_error = false;
	bool otro_socket_cerrado = false;
	while(b_env<bytes_enviar&&socket_error==false&&otro_socket_cerrado==false){
		bytes_exito=send(this->skt,texto,bytes_enviar-b_env,MSG_NOSIGNAL);
		if(bytes_exito==CERO){
			otro_socket_cerrado=true;
		}else if (bytes_exito<CERO){
			socket_error=true;
		}else{
			b_env += bytes_exito;
			texto += bytes_exito;
		}
	}
	if(socket_error||otro_socket_cerrado){
		return INVALID;
	}
	return CERO;
}

int Socket::recibir(char* texto,int cantidad){
	int bytes_recb = cantidad;
	int recibidos = CERO;
	int recib_ant = CERO;
	int bytes_exitosos;
	bool socket_error = false;
	bool otro_socket_cerr = false;
	while(recibidos<bytes_recb&&socket_error==false&&otro_socket_cerr==false){
		bytes_exitosos=recv(this->skt,texto,bytes_recb-recibidos,MSG_NOSIGNAL);
		if(bytes_exitosos==CERO){
			if(recib_ant!=CERO){
				return recib_ant;
			}
			otro_socket_cerr=true;
		}else if (bytes_exitosos<CERO){
			socket_error=true;
		}else{
			recib_ant = bytes_exitosos;
			recibidos += bytes_exitosos;
			texto += bytes_exitosos;
		}
	}
	if(socket_error||otro_socket_cerr){
		return CERO; 
	}
	return recibidos;
}



Socket::~Socket(){
	shutdown(this->skt,SHUT_RDWR); 
	close(this->skt);
}

