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
    uint16_t id;
    Socket conexion_socket;
    std::atomic_bool esta_cerrado;
    Queue<EstadoJuego>& estados_juego;
    Queue<EventoServer>& eventos;
    bool dos_jugadores;
    ServerEnviar enviar;
    

    void cerrar(ServerEnviar& enviar);

public:
    ServerClient(uint16_t id, Socket skt, Queue<EstadoJuego>& recibidos, Queue<EventoServer>& enviados);
    void run() override;
    uint16_t& get_id();
    void juegan_2_personas();
    bool juegan_dos();
    Queue<EventoServer>& get_queue();
    void enviar_estado(EstadoJuego& estado);
    void cambiar_queue(Queue<EstadoJuego>* nueva_queue);
};

#endif
