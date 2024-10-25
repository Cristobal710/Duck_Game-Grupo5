#ifndef CLIENTE_RECIBIR_H
#define CLIENTE_RECIBIR_H

#include "../common/common_estado_juego.h"
#include "../common/common_protocolo.h"
#include "../common/common_queue.h"

#include "cliente_comando.h"
#include "cliente_protocolo.h"
class ClienteRecibir {
private:
    ClienteProtocolo protocolo;
    Queue<EstadoJuego>& cola_estados_juego;

public:
    ClienteRecibir(Socket& socket, Queue<EstadoJuego>& cola_estados_juego);
    void run();
};

#endif
