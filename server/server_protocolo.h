#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H

#include <iostream>
#include <string>
#include <vector>

#include "../common/common_queue.h"
#include "../common/common_socket.h"

class ServerProtocolo {
private:
    Socket& socket;
    bool* esta_cerrado;

    std::vector<uint8_t> recibir_nombre();
    uint8_t recibir_caja();

public:
    ServerProtocolo(Socket& socket, bool* esta_cerrado);

    /*0x06 0x04 <player-name> <reward-id>, donde el <reward-id> es un byte con el id de la
    recompensa. Este método indica que un jugador recogió el premio de una caja.*/
    int enviar_reward(std::string& nombre, uint8_t* reward_id);

    /*0x06 0x05 para indicar que una caja reapareció.*/
    int enviar_nueva_caja();

    void recibir_pickup(Queue<std::string>* recibidos);
};

#endif
