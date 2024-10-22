#include "cliente_protocolo.h"

#include <cstring>
#include <iostream>

#include <arpa/inet.h>

#include "common_liberror.h"

ClienteProtocolo::ClienteProtocolo(Socket& socket): Protocolo(socket) {}

void ClienteProtocolo::enviar_interaccion(const uint8_t accion, const uint8_t jugador_id){
    enviar_byte(BYTE_INTERACTUAR);
    enviar_byte(accion);
    enviar_byte(jugador_id);
}


void ClienteProtocolo::enviar_movimiento(const uint8_t movimiento, const uint8_t jugador_id){
    enviar_byte(BYTE_MOVER);
    enviar_byte(movimiento);
    enviar_byte(jugador_id);
}

