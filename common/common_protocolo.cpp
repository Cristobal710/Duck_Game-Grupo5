#include "common_protocolo.h"

#include "common_liberror.h"

Protocolo::Protocolo(Socket& socket): socket(socket), acciones() {
    acciones["d"] = MOVER_DERECHA;
    acciones["a"] = MOVER_IZQUIERDA;
    acciones["w"] = APUNTAR_ARRIBA;
    acciones[" "] = SALTAR_ALETEAR;
    acciones["click_izq"] = DISPARAR;
    acciones["r"] = RECARGAR;
    acciones["e"] = TOMAR_ARMA;
    acciones["q"] = TIRAR_PISO;
}

void Protocolo::enviar_byte(uint8_t byte) { byte++; }

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
