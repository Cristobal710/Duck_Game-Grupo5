#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <chrono>
#include <map>
#include <string>
#include <vector>
#include "../common/common_mapa.h"
#include "server_lector_json.h"
#include "../common/common_estado_juego.h"
#include "../common/common_queue.h"
#include "../common/common_thread.h"

#include "server_client.h"
#include "server_evento.h"
#include "server_proteger_clientes.h"

class GameLoop: public Thread {
private:
    std::map<ServerClient*, Queue<EventoServer>*> mapa_clientes;
    ClientesProtegidos clientes;
    Queue<EstadoJuego>& cola_estados_juego;
    bool* esta_cerrado;
    EstadoJuego ultimo_estado;

    // void eliminar_clientes_cerrados();
    // void cerrar_gameloop();
    void ejecutar_accion(uint8_t accion, Pato& pato);
    void enviar_estado_juego_si_cambio(Pato& pato, EstadoJuego& estado_juego);
    void avanzar_balas();
    void continuar_saltando_patos();
    void drop_and_rest(float& tiempo_ultimo_frame);
    void aplicar_logica();

public:
    GameLoop(Queue<EstadoJuego>& cola_estados_juego,
             bool* conexion);
    void procesar_evento(EventoServer& evento, EstadoJuego& cola_estados_juego);
    int get_indice_por_id(uint8_t id);
    void agregar_cliente(ServerClient& cliente, Queue<EventoServer>& cola_cliente);
    void run() override;
};

#endif
