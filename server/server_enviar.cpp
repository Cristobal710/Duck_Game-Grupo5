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

ServerEnviar::ServerEnviar(Socket& skt, Queue<std::string>& enviados):
        socket(skt), enviados(enviados), esta_cerrado(false) {}

void ServerEnviar::run() {
    ServerProtocolo server_protocolo(socket, &esta_cerrado);

    while (!esta_cerrado) {
        try {
            std::string mensaje = enviados.pop();
            if (mensaje == CAJA_NUEVA) {
                server_protocolo.enviar_nueva_caja();
            } else {
                std::string nombre = mensaje.substr(0, mensaje.find(PICKED_UP_A));
                uint8_t reward_id = 0;
                if (mensaje.find(BAZOOKA) != std::string::npos) {
                    reward_id = REWARD_ID_BAZOOKA;
                } else if (mensaje.find(CHAINSAW) != std::string::npos) {
                    reward_id = REWARD_ID_CHAINSAW;
                } else if (mensaje.find(DEATH_RAY) != std::string::npos) {
                    reward_id = REWARD_ID_DEATH_RAY;
                } else if (mensaje.find(SHOTGUN) != std::string::npos) {
                    reward_id = REWARD_ID_SHOTGUN;
                }
                server_protocolo.enviar_reward(nombre, (&reward_id));
            }
        } catch (ClosedQueue& e) {
            break;
        } catch (...) {
            break;
        }
    }

    esta_cerrado = true;
    _is_alive = false;
}
