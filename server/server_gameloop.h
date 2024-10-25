#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <chrono>
#include <map>
#include <string>
#include <vector>

#include "../common/common_queue.h"
#include "../common/common_thread.h"

#include "server_client.h"
#include "server_proteger_clientes.h"

class GameLoop: public Thread {
private:
    std::map<ServerClient*, Queue<std::string>*> mapa;
    ClientesProtegidos clientes;
    Queue<std::string>& cola_pedidos;
    bool* esta_cerrado;

    void sleep_a_little();
    void eliminar_clientes_cerrados();
    void cerrar_gameloop();
    void sumar_iteracion(bool caja_disponible, int& contador_caja);
    void agregar_caja_nueva(int& contador, int caja_nueva, bool& caja_disponible);
    void manejo_mensaje(std::string mensaje, bool& bazooka_disponible);
    void elegir_caja(std::string mensaje, bool& bazooka_disponible, bool& chainsaw_disponible,
                     bool& death_ray_disponible, bool& shotgun_disponible);

public:
    GameLoop(Queue<std::string>& cola_pedidos, bool* conexion);
    void agregar_cliente(ServerClient& cliente, Queue<std::string>& cola_cliente);
    void run() override;
};

#endif
