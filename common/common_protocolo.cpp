#include "common_protocolo.h"

#include "common_liberror.h"

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


Protocolo::Protocolo(Socket& socket): socket(socket) {}

void esta_cerrado(const bool& cerrado, const std::string& mensaje) {
    if (cerrado) {
        throw LibError(errno, mensaje.c_str());
    }
}

std::string Protocolo::recibir_string(bool& cerrado) {
    std::vector<uint8_t> size(2);
    socket.recvall(size.data(), size.size(), &cerrado);
    esta_cerrado(cerrado, "Connection closed while receiving byte");
    uint16_t largo = size[0] << 8 | size[1];
    std::vector<uint8_t> datos(largo);
    socket.recvall(datos.data(), datos.size(), &cerrado);
    esta_cerrado(cerrado, "Connection cerrado while receiving name");
    std::string mensaje(datos.begin(), datos.end());
    return mensaje;
}

uint8_t Protocolo::recibir_byte(bool& cerrado) {
    std::vector<uint8_t> datos(1);
    socket.recvall(datos.data(), datos.size(), &cerrado);
    esta_cerrado(cerrado, "Coneccion cerrada while receiving uint8_t");
    return datos[0];
}
