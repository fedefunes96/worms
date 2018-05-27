#ifndef SOCKET_H
#define SOCKET_H
#include <string>

//version 1 en la cual socket por default arma un cliente.. y tengo otra clase
// hereda y hace Server
class Socket{
    private: // para que las clases que hereden, puedan modificar y tener acs
        int skt;
        int fd;
        void set_skt(int skt);
        void set_fd(int fd);
        bool server;
        Socket();
        //fin priv
    public:
        /*Constructor: intenta crear la conexion segun sea si es para cliente
        o servidor */
        Socket(const std::string& ip,const std::string& puerto);
        /*Constructor por movimiento*/
        Socket(Socket&& other);
        /*Destructor: se elimina de memoria los paquetes*/
        virtual ~Socket();
        /*Enviar: envia la cantidad especificada del string pasado por 
        parametro. En caso de error se devuuelve -1, sino 0*/
        int enviar(const char* texto, int cantidad);
        /*Recibir: espera leer de la conexion la cantidad pasada por 
        parametro, para ir guardandola en el string texto. En caso de 
        error se devuelve int -1 sino 0*/
        int recibir(char* texto, int cantidad);
        /*Constructor del servidor, recibe como string el puerto por el 
        cual se desea abrir el server.*/
        explicit Socket(const std::string& puerto);
        /*Metodo para el socket tipo server. Acepta conexiones, devolviendo
        un puntero, en caso que no sea tipo server o error, se devuelve
        nullptr.*/
        Socket* server_aceptar_clt();
};


#endif
