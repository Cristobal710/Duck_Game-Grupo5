#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "interfaz_grafica.h"
#include "cliente_enviar.h"
#include "cliente_recibir.h"
#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "cliente_protocolo.h"
/*
 * Clase para encapsular al cliente que se conectara con el servidor
 * */
class Client : public Thread{
public:
    explicit Client(const char* hostname, const char* servname, std::atomic_bool& cerrar_programa);
    /*
     * Ejecuta el cliente que inicializa el protocolo y se conecta con el servidor
     * */
    void run() override;

private:
    Socket socket;
    std::atomic_bool& cerrar_programa;
};

#endif
