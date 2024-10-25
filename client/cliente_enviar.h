#ifndef CLIENTE_SENDER_H
#define CLIENTE_SENDER_H


#include "../common/common_queue.h"
#include "../common/common_thread.h"

#include "cliente_comando.h"
#include "cliente_protocolo.h"


class ClientEnviar {
private:
    ClienteProtocolo protocolo;
    Queue<ComandoGrafica> eventos;

public:
    explicit ClientEnviar(Socket& socket);
    void enviar_comando();
    void run();
};

#endif
