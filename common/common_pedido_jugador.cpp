#include "common_pedido_jugador.h"


PedidoJugador::PedidoJugador(): crear_partida(0), unirse_a_partida(0),
    id_partida_a_unirse(0), un_jugador(0), dos_jugadores(0) {}

void PedidoJugador::partida_nueva() {
    crear_partida = 0x01;
    unirse_a_partida = BYTE_NULO;
    id_partida_a_unirse = BYTE_NULO;
    un_jugador = BYTE_NULO;
    dos_jugadores = BYTE_NULO;
}

void PedidoJugador::unirse_a_partida_con_id(uint8_t id_partida) {
    crear_partida = BYTE_NULO;
    unirse_a_partida = 0x01;
    id_partida_a_unirse = id_partida;
    un_jugador = BYTE_NULO;
    dos_jugadores = BYTE_NULO;
}

void PedidoJugador::juega_uno_solo() {
    crear_partida = BYTE_NULO;
    unirse_a_partida = BYTE_NULO;
    id_partida_a_unirse = BYTE_NULO;
    un_jugador = 0x01;
    dos_jugadores = BYTE_NULO;
}

void PedidoJugador::juegan_dos_personas() {
    crear_partida = BYTE_NULO;
    unirse_a_partida = BYTE_NULO;
    id_partida_a_unirse = BYTE_NULO;
    un_jugador = BYTE_NULO;
    dos_jugadores = 0x01;
}

void PedidoJugador::iniciar_partida() {
    crear_partida = BYTE_NULO;
    unirse_a_partida = BYTE_NULO;
    id_partida_a_unirse = BYTE_NULO;
    un_jugador = BYTE_NULO;
    dos_jugadores = BYTE_NULO;
    empezar = 0x01;
}
