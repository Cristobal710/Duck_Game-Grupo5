#ifndef SERVER_PROTEGER_CLIENTES_H
#define SERVER_PROTEGER_CLIENTES_H

#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <list>
#include "../common/common_queue.h"

#include "server_client.h"


class ClientesProtegidos {
private:
    std::mutex mutex;
    std::map<ServerClient*, Queue<EventoServer>*>& clientes;

public:
    explicit ClientesProtegidos(std::map<ServerClient*, Queue<EventoServer>*>& mapa_clientes);
    void agregar_cliente(ServerClient& cliente, Queue<EventoServer>& enviados);
    std::vector<EventoServer> recibir_mensajes_clientes();
    void eliminar_clientes_cerrados();
    void cerrar_gameloop();
    std::vector<uint16_t> obtener_ids();
};

#endif
