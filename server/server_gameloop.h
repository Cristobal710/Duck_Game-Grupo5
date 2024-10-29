#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <chrono>
#include <map>
#include <string>
#include <vector>

#include "../common/common_estado_juego.h"
#include "../common/common_queue.h"
#include "../common/common_thread.h"

#include "server_client.h"
#include "server_evento.h"
#include "server_proteger_clientes.h"

class GameLoop: public Thread {
private:
    // ClientesProtegidos clientes;
    Queue<EventoServer>& cola_eventos;
    Queue<EstadoJuego>& cola_estados_juego;
    bool* esta_cerrado;
    EstadoJuego ultimo_estado;

    // void agregar_cliente(ServerClient& cliente, Queue<std::string>& cola_cliente);
    // void eliminar_clientes_cerrados();
    // void cerrar_gameloop();
    void ejecutar_accion(uint8_t accion, Pato& pato);

public:
    GameLoop(Queue<EventoServer>& cola_eventos, Queue<EstadoJuego>& cola_estados_juego,
             bool* conexion);
    void procesar_evento(EventoServer& evento, EstadoJuego& cola_estados_juego);
    int get_indice_por_id(uint8_t id);
    // void agregar_cliente(ServerClient& cliente, Queue<std::string>& cola_cliente);
    void run() override;
};

#endif
