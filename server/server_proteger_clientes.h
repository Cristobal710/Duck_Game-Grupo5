#ifndef SERVER_PROTEGER_CLIENTES_H
#define SERVER_PROTEGER_CLIENTES_H

#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>

#include "../common/common_queue.h"
#include "server_client.h"


class ClientesProtegidos {
private:
    std::mutex mutex;
    std::map<ServerClient*, Queue<std::string>*>& clientes;

public:
    explicit ClientesProtegidos(std::map<ServerClient*, Queue<std::string>*>& mapa_clientes);
    void agregar_cliente(ServerClient& cliente, Queue<std::string>& enviados);
    void enviar_mensajes_clientes(std::string mensaje);
    void eliminar_clientes_cerrados();
    void cerrar_gameloop();
};

#endif
