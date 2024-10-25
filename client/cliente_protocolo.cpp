#include "cliente_protocolo.h"

#include <cstring>
#include <iostream>

#include <arpa/inet.h>

#include "../common/common_liberror.h"

ClienteProtocolo::ClienteProtocolo(Socket& socket): Protocolo(socket) {}

void ClienteProtocolo::enviar_comando(ComandoGrafica comando) {
    uint8_t accion = acciones[comando.tecla];
    enviar_byte(accion);
    enviar_byte(comando.jugador_id);
}

EstadoJuego ClienteProtocolo::recibir_estado_juego() {
    EstadoJuego estado_juego;
    estado_juego.estado = {0x01};
    // bool cerrado;
    //  serializar el estado del juego
    return estado_juego;
}
