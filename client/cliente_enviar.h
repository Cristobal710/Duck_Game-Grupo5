#ifndef CLIENTE_SENDER_H
#define CLIENTE_SENDER_H


#include "cliente_protocolo.h"
#include "../common/common_thread.h"
#include "../common/common_queue.h"
#include "cliente_comando.h"


class ClientEnviar {
    private:
        ClienteProtocolo protocolo;
        Queue<ComandoGrafica> eventos;
    public:
        ClientEnviar(Socket& socket);
        void enviar_comando();
        void run();
};

#endif
