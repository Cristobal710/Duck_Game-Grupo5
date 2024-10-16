#ifndef SERVER_ACCEPTER_H
#define SERVER_ACCEPTER_H

#include <list>
#include <string>
#include <utility>

#include "common_queue.h"
#include "common_socket.h"
#include "common_thread.h"
#include "server_client.h"
#include "server_gameloop.h"

class Accepter: public Thread {
private:
    Socket& socket_aceptador;
    bool* esta_cerrado;
    Queue<std::string> recibidos;

public:
    Accepter(Socket& socket, bool* conexion);
    void run() override;
};


#endif
