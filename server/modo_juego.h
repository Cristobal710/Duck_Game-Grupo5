#ifndef MODO_JUEGO_H
#define MODO_JUEGO_H
#include <chrono>
#include <map>
#include <string>
#include <vector>
#include "../common/common_thread.h"
#include "server_client.h"
#include "server_evento.h"
#include "queue_protegida.h"

class ModoJuego: public Thread {
    private:
    ServerClient& cliente;
    Queue<EventoServer>& queue_cliente;
    QueueProtegida broadcast;
    EstadoJuego ultimo_estado;
    uint8_t id_partida;
    std::list<ModoJuego*>& partidas_distintas;
    bool partida_nueva;

    void procesar_evento_lobby(EventoServer& evento, bool& iniciar_partida);
    void drop_and_rest(float& tiempo_ultimo_frame);
    void ejecutar_accion_lobby(PedidoJugador& pedido, uint16_t id_jugador, bool& iniciar_partida);


    public:
    ModoJuego(ServerClient& cliente, Queue<EventoServer>& cola_cliente, Queue<EstadoJuego>& recibidos, uint8_t id,
    std::list<ModoJuego*>& partidas_distintas);
    void run() override;
    bool tiene_partida();
    uint8_t obtener_id_partida();

    
};



#endif

