#ifndef SERVER_RECIBIR_H
#define SERVER_RECIBIR_H

#include <string>

#include "../common/common_estado_juego.h"
#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"

#include "server_evento.h"
#include "server_protocolo.h"


class ServerRecibir {
private:
    Socket& skt;
    Queue<EventoServer>& cola_eventos;

public:
    ServerRecibir(Socket& skt, Queue<EventoServer>& cola_eventos);
    void run();
};


#endif
