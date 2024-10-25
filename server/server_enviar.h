#ifndef SERVER_ENVIAR_H
#define SERVER_ENVIAR_H

#include <string>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "../common/common_estado_juego.h"
#include "server_protocolo.h"

class ServerEnviar: public Thread {
private:
    Socket& socket;
    Queue<EstadoJuego>& estados_juego;
    bool esta_cerrado;

public:
    ServerEnviar(Socket& skt, Queue<EstadoJuego>& estados_juego);
    void run() override;
};

#endif
