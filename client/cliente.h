#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "cliente_protocolo.h"
#include "common_socket.h"
#include "common_thread.h"
#include "common_queue.h"
/*
 * Clase para encapsular al cliente que se conectara con el servidor
 * */
class Client {
public:
    explicit Client(Socket& client_socket);
    /*
     * Ejecuta el cliente que inicializa el protocolo y se conecta con el servidor
     * */
    void run();

private:
    Socket& socket;
};

#endif
