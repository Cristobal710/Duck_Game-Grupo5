#include "server_protocolo.h"

#define EXITO 0
#define ERROR 1

#define BYTE_NULO 0x00
#define BYTE_0X06 0x06
#define BYTE_0X05 0x05
#define BYTE_0X04 0x04

#define PICKED_UP_A " picked up a "

#define ID_CAJA_BAZOOKA 0x01
#define ID_CAJA_CHAINSAW 0x02
#define ID_CAJA_DEATH_RAY 0x03
#define ID_CAJA_SHOTGUN 0x04

#define BAZOOKA "Bazooka"
#define CHAINSAW "Chainsaw"
#define DEATH_RAY "Death ray"
#define SHOTGUN "Shotgun"

#define ID_INVALIDO "El ID de la caja es invalido"

ServerProtocolo::ServerProtocolo(Socket& skt, bool* conexion):
        socket(skt), esta_cerrado(conexion) {}

std::vector<uint8_t> ServerProtocolo::recibir_nombre() {
    // largo nombre
    std::vector<uint8_t> largo_nombre(3);
    socket.recvall(largo_nombre.data(), largo_nombre.size(), esta_cerrado);
    if (*esta_cerrado) {
        return {};
    }
    uint16_t largo = largo_nombre[2];
    // nombre
    std::vector<uint8_t> nombre(largo);
    socket.recvall(nombre.data(), nombre.size(), esta_cerrado);
    if (*esta_cerrado) {
        return {};
    }
    return nombre;
}

uint8_t ServerProtocolo::recibir_caja() {
    // id caja
    uint8_t caja_id = 0;
    socket.recvall(&caja_id, sizeof(caja_id), esta_cerrado);
    if (*esta_cerrado) {
        return 0;
    }
    return caja_id;
}

int ServerProtocolo::enviar_reward(std::string& nombre, uint8_t* reward_id) {
    int ret = EXITO;
    std::vector<uint8_t> mensaje_codificado;

    mensaje_codificado.insert(mensaje_codificado.begin(), BYTE_0X06);
    mensaje_codificado.insert(mensaje_codificado.end(), BYTE_0X04);

    mensaje_codificado.insert(mensaje_codificado.end(), BYTE_NULO);

    uint16_t largo_nombre = static_cast<uint16_t>(nombre.size());
    mensaje_codificado.insert(mensaje_codificado.end(), largo_nombre);
    mensaje_codificado.insert(mensaje_codificado.end(), nombre.begin(), nombre.end());

    mensaje_codificado.insert(mensaje_codificado.end(), (*reward_id));

    int bytes_enviados =
            socket.sendall(mensaje_codificado.data(), mensaje_codificado.size(), esta_cerrado);

    if (bytes_enviados != static_cast<int>(mensaje_codificado.size())) {
        ret = ERROR;
    }
    if (esta_cerrado) {
        return ret;
    }
    return ret;
}

int ServerProtocolo::enviar_nueva_caja() {
    int ret = EXITO;
    std::vector<uint8_t> mensaje_codificado;

    mensaje_codificado.insert(mensaje_codificado.begin(), BYTE_0X06);
    mensaje_codificado.insert(mensaje_codificado.end(), BYTE_0X05);

    int bytes_enviados =
            socket.sendall(mensaje_codificado.data(), mensaje_codificado.size(), esta_cerrado);

    if (bytes_enviados != static_cast<int>(mensaje_codificado.size())) {
        ret = ERROR;
    }
    if (esta_cerrado) {
        return ret;
    }
    return ret;
}

void ServerProtocolo::recibir_pickup(Queue<std::string>* recibidos) {

    std::string mensaje_completo = PICKED_UP_A;

    std::vector<uint8_t> nombre = recibir_nombre();
    mensaje_completo.insert(mensaje_completo.begin(), nombre.begin(), nombre.end());

    uint8_t caja_id = recibir_caja();
    std::string caja;
    switch (caja_id) {
        case ID_CAJA_BAZOOKA:
            caja = BAZOOKA;
            mensaje_completo.insert(mensaje_completo.end(), caja.begin(), caja.end());
            break;
        case ID_CAJA_CHAINSAW:
            caja = CHAINSAW;
            mensaje_completo.insert(mensaje_completo.end(), caja.begin(), caja.end());
            break;
        case ID_CAJA_DEATH_RAY:
            caja = DEATH_RAY;
            mensaje_completo.insert(mensaje_completo.end(), caja.begin(), caja.end());
            break;
        case ID_CAJA_SHOTGUN:
            caja = SHOTGUN;
            mensaje_completo.insert(mensaje_completo.end(), caja.begin(), caja.end());
            break;
        default:
            throw std::runtime_error(ID_INVALIDO);
    }

    if (mensaje_completo == PICKED_UP_A) {
        return;
    }

    (*recibidos).push(mensaje_completo);
}
