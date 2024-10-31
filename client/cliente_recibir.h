#ifndef CLIENTE_RECIBIR_H
#define CLIENTE_RECIBIR_H

#include "../common/common_estado_juego.h"
#include "../common/common_protocolo.h"
#include "../common/common_queue.h"
#include "../common/common_thread.h"
#include "cliente_comando.h"
#include "cliente_protocolo.h"
class ClienteRecibir : public Thread {
private:
    ClienteProtocolo protocolo;
    Queue<EstadoJuego>& cola_estados_juego;

public:
    ClienteRecibir(Socket& socket, Queue<EstadoJuego>& cola_estados_juego);
    void run() override;
};

#endif
