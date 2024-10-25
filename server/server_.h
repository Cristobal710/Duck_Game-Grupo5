#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <utility>

#include "../common/common_socket.h"

#include "server_accepter.h"
#include "server_gameloop.h"

class Server {
private:
    Socket socket_aceptador;
    bool esta_cerrado;

    void cerrar(Accepter& aceptador);

public:
    explicit Server(const char* servname);
    int run();
};

#endif
