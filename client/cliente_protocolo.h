#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <vector>

#include "../common/common_protocolo.h"
#include "../common/common_socket.h"

/*
 * Clase para encapsular el protocolo de comunicacion con el servidor
 * */
class ClienteProtocolo: public Protocolo {
    public:
        explicit ClienteProtocolo(Socket& socket);

        void enviar_interaccion(const uint8_t accion, const uint8_t jugador_id);

        void enviar_movimiento(const uint8_t movimiento, const uint8_t jugador_id);
};

#endif
