#ifndef COMMON_PROTOCOLO_H
#define COMMON_PROTOCOLO_H

#include <string>
#include <vector>
#include <cstdint>
#include "common_socket.h"

#define BYTE_NULO 0x00

#define BYTE_MOVER 0x10
#define MOVER_IZQUIERDA 0x01
#define MOVER_DERECHA 0x02
#define MOVER_ABAJO 0x03
#define SALTAR_ALETEAR 0x04


#define BYTE_INTERACTUAR 0x20
#define DISPARAR 0x21
#define APUNTAR_ARRIBA 0x22
#define TIRAR_PISO 0x23
#define MORIR 0x24
#define RECIBIR_IMPACTO 0x25

#define TOMAR_ARMA 0X26

// El mensaje del protocolo tendría este formato: [byte de comando](mover o interactuar) [byte de acción] [byte de jugador_id]

class Protocolo {
    protected:
        Socket& socket;

    public:
        explicit Protocolo(Socket& socket);

        void enviar_byte(const uint8_t byte);

    protected:
        std::string recibir_string(bool& closed);
        uint8_t recibir_byte(bool& closed);
};

#endif
