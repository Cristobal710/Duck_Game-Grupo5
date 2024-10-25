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

ServerEnviar::ServerEnviar(Socket& skt, Queue<EstadoJuego>& estados_juego):
        socket(skt), estados_juego(estados_juego){}


void ServerEnviar::run() {
    ServerProtocolo server_protocolo(socket);
    while (!esta_cerrado) {
        try{
            EstadoJuego nuevo_estado = estados_juego.pop();
            server_protocolo.enviar_estado_juego(nuevo_estado);
        } catch (ClosedQueue& e) {
            break;
        } catch (...) {
            break;
        }
    }

}
