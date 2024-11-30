#ifndef MODO_JUEGO_H
#define MODO_JUEGO_H
#include <chrono>
#include <map>
#include <string>
#include <vector>
#include "../common/common_estado_juego.h"
#include "../common/common_queue.h"
#include "../common/common_thread.h"
#include "server_client.h"
#include "server_evento.h"

class ModoJuego: public Thread {
    private:
    ServerClient& cliente;
    Queue<EventoServer>& queue_cliente;
    Queue<EstadoJuego>& broadcast;
    EstadoJuego ultimo_estado;
    uint8_t id_partida;

    void procesar_evento_lobby(EventoServer& evento, bool& iniciar_partida, bool& partida_nueva);
    void drop_and_rest(float& tiempo_ultimo_frame);
    void ejecutar_accion_lobby(PedidoJugador& pedido, uint16_t id_jugador, bool& iniciar_partida, bool& partida_nueva);


    public:
    ModoJuego(ServerClient& cliente, Queue<EventoServer>& cola_cliente, Queue<EstadoJuego>& recibidos, uint8_t id);
    void run() override;
    
};



#endif

