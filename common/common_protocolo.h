#ifndef COMMON_PROTOCOLO_H
#define COMMON_PROTOCOLO_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "../common/common_constantes.h"
#include "../common/common_estado_juego.h"

#include "common_socket.h"

// El mensaje del protocolo tendría este formato: [byte de comando](mover o interactuar) [byte de
// acción] [byte de jugador_id]

class Protocolo {
protected:
    Socket& socket;
    std::map<std::string, uint8_t> acciones;

public:
    explicit Protocolo(Socket& socket);

    void enviar_byte(const uint8_t byte);
    void enviar_dos_bytes(const uint16_t valor);
    uint16_t recibir_dos_bytes(bool& cerrado);
    void esta_cerrado(const bool& cerrado, const std::string& mensaje);


protected:
    std::string recibir_string(bool& closed);
    uint8_t recibir_byte(bool& closed);
};

#endif
