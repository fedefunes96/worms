#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

class Thread {
    private:
        std::thread thread;
    public:
        /*Constructor*/
        Thread();
        /*Crea e inicializa el thread con functor run*/
        void start();
        /*Hace el  join del thread*/
        void join();
        /*Metodo run a ser implementado si se hereda o implementa la clase*/
        virtual void run() = 0;
        /*Destructor*/
        virtual ~Thread();
        /*Constructor por copia no permitido*/
        Thread(const Thread&) = delete;
        /*Operador = no permitido*/
        Thread& operator=(const Thread&) = delete;
        /*Constructor por movimiento*/
        Thread(Thread&& other);
        /*Operador = no permitido*/
        Thread& operator=(Thread&& other);
};

#endif // THREAD_H
