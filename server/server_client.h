#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"

#include "server_enviar.h"
#include "server_protocolo.h"

class ServerClient: public Thread {
private:
    Socket conexion_socket;
    bool esta_cerrado;
    Queue<EstadoJuego>& estados_juego;
    Queue<EventoServer>& eventos;

    void cerrar(ServerEnviar& enviar);

public:
    ServerClient(Socket skt, Queue<EstadoJuego>& recibidos, Queue<EventoServer>& enviados);
    void run() override;
};

#endif
