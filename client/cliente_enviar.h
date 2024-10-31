#ifndef CLIENTE_SENDER_H
#define CLIENTE_SENDER_H


#include "../common/common_queue.h"
#include "../common/common_thread.h"

#include "cliente_comando.h"
#include "cliente_protocolo.h"


class ClientEnviar : public Thread{
private:
    ClienteProtocolo protocolo;
    Queue<ComandoGrafica>& eventos;

public:
    explicit ClientEnviar(Socket& socket, Queue<ComandoGrafica>& cola_eventos);
    void enviar_comando();
    void run() override;
};

#endif
