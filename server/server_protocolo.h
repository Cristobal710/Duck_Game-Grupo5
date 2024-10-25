#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "../common/common_protocolo.h"
#include "../common/common_queue.h"
#include "../common/common_socket.h"

#include "server_evento.h"

struct Comando {
    uint8_t comando;
    uint8_t accion;
    uint8_t jugador_id;
};

class ServerProtocolo: public Protocolo {
private:
    Comando recibir_nombre();
    uint8_t recibir_caja();

public:
    explicit ServerProtocolo(Socket& socket);
    EventoServer recibir_evento();
    void enviar_estado_juego(EstadoJuego& estado);
};

#endif
