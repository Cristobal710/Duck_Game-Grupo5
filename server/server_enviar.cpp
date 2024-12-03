#include "server_enviar.h"

#define CAJA_NUEVA "A new box has appeared"
#define PICKED_UP_A " picked up a "

#define REWARD_ID_BAZOOKA 0x10
#define REWARD_ID_CHAINSAW 0x11
#define REWARD_ID_DEATH_RAY 0x12
#define REWARD_ID_SHOTGUN 0x13

#define BAZOOKA "Bazooka"
#define CHAINSAW "Chainsaw"
#define DEATH_RAY "Death ray"
#define SHOTGUN "Shotgun"

ServerEnviar::ServerEnviar(Socket& skt, Queue<EstadoJuego>* estados_juego, std::atomic_bool& esta_cerrado):
        socket(skt), estados_juego(estados_juego), server_protocolo(socket), esta_cerrado(esta_cerrado) {}


void ServerEnviar::run() {
    
    while (!esta_cerrado) {
        try {
            EstadoJuego nuevo_estado = estados_juego->pop();
            server_protocolo.enviar_estado_juego(nuevo_estado);
        } catch (ClosedQueue& e) {
            continue;
        }
    }
}

void ServerEnviar::enviar_estado(EstadoJuego& estado) {
    server_protocolo.enviar_estado_juego(estado);
}


void ServerEnviar::cerrar_queue() {
    estados_juego->close();
}

void ServerEnviar::cambiar_queue(Queue<EstadoJuego>* nueva_queue) {
    estados_juego->close();
    estados_juego = nueva_queue;
}
