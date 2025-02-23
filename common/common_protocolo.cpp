#include "common_protocolo.h"

#include "common_liberror.h"

Protocolo::Protocolo(Socket& socket): socket(socket), acciones() {
    acciones[DERECHA] = MOVER_DERECHA;
    acciones[IZQUIERDA] = MOVER_IZQUIERDA;
    acciones[ARRIBA] = APUNTAR_ARRIBA;
    acciones[SALTO] = SALTAR;
    acciones[DISPARO] = DISPARAR;
    acciones[ABAJO] = TIRAR_PISO;
    acciones[AGARRAR_ARMA] = AGARRAR_RECOMPENSA;
    acciones[TIRAR_ARMA] = SOLTAR_ARMA;
    acciones[NO_DERECHA] = DEJAR_MOVER_DERECHA;
    acciones[NO_IZQUIERDA] = DEJAR_MOVER_IZQUIERDA;
    acciones[NO_ARRIBA] = DEJAR_APUNTAR_ARRIBA;
    acciones[NO_SALTO] = DEJAR_SALTAR;
    acciones[NO_ABAJO] = DEJAR_TIRAR_PISO;
}

void Protocolo::enviar_byte(const uint8_t byte) { 
    std::vector<uint8_t> data(1, byte);
    bool berretin;
    socket.sendall(data.data(), data.size(), &berretin);
}

uint8_t Protocolo::recibir_byte(bool& cerrado) {
    std::vector<uint8_t> datos(1);
    socket.recvall(datos.data(), datos.size(), &cerrado);
    esta_cerrado(cerrado, "Coneccion cerrada while receiving uint8_t");
    return datos[0];
}

/*void Protocolo::enviar_dos_bytes(const uint16_t valor) {
    std::vector<uint8_t> data(2);
    data[0] = (valor >> 8) & 0xFF;  // Byte más significativo
    data[1] = valor & 0xFF;         // Byte menos significativo
    bool cerrado;
    socket.sendall(data.data(), data.size(), &cerrado);
}*/

void Protocolo::enviar_dos_bytes(uint16_t value) {
    uint8_t buffer[2];
    buffer[0] = (value >> 8) & 0xFF;  // High byte
    buffer[1] = value & 0xFF;         // Low byte
    bool cerrado;
    socket.sendall(buffer, 2, &cerrado);
}

uint16_t Protocolo::recibir_dos_bytes( bool& cerrado) {
    std::vector<uint8_t> datos(2);
    socket.recvall(datos.data(), datos.size(), &cerrado);
    esta_cerrado(cerrado, "Conexión cerrada while receiving uint16_t");
    return (datos[0] << 8) | datos[1];
}



void Protocolo::esta_cerrado(const bool& cerrado, const std::string& mensaje) {
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

