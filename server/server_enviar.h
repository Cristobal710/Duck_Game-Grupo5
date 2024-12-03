#ifndef SERVER_ENVIAR_H
#define SERVER_ENVIAR_H

#include <string>

#include "../common/common_estado_juego.h"
#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"

#include "server_protocolo.h"

class ServerEnviar: public Thread {
private:
    Socket& socket;
    Queue<EstadoJuego>* estados_juego;
    ServerProtocolo server_protocolo;
    std::atomic_bool& esta_cerrado;

public:
    ServerEnviar(Socket& skt, Queue<EstadoJuego>* estados_juego, std::atomic_bool& esta_cerrado);
    void run() override;
    void iniciar_partida(EstadoJuego& estado);
    void cambiar_queue(Queue<EstadoJuego>* nueva_queue);
    void cerrar_queue();
};

#endif
