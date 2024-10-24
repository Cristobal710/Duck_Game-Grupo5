#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <vector>
#include "cliente_comando.h"
#include "../common/common_protocolo.h"
#include "../common/common_socket.h"
#include <map>

/*
 * Clase para encapsular el protocolo de comunicacion con el servidor
 * */
class ClienteProtocolo: public Protocolo {

    public:
        explicit ClienteProtocolo(Socket& socket);

        void enviar_comando(ComandoGrafica comando);

        EstadoJuego recibir_estado_juego();
};

#endif
