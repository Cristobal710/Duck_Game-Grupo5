#include "common_estado_pato.h"

// EstadoPato::EstadoPato():
//         estado_movimiento(BYTE_NULO),
//         estado_salto(BYTE_NULO) {}

EstadoPato::EstadoPato():
        estado_movimiento(BYTE_NULO) {}

// EstadoPato::EstadoPato(uint8_t estado_movimiento, uint8_t estado_salto):
//         estado_movimiento(estado_movimiento),
//         estado_salto(estado_salto) {}

EstadoPato::EstadoPato(uint8_t estado_movimiento): estado_movimiento(estado_movimiento) {}

uint8_t EstadoPato::get_estado_movimiento() { return estado_movimiento; }

//uint8_t EstadoPato::get_estado_salto() { return estado_salto; }

void EstadoPato::set_moviendo_derecha() { estado_movimiento = MOVER_DERECHA; }

void EstadoPato::set_moviendo_izquierda() { estado_movimiento = MOVER_IZQUIERDA; }

void EstadoPato::set_dejar_de_moverse() { estado_movimiento = BYTE_NULO; }

// void EstadoPato::set_saltar() { estado_salto = SALTAR_ALETEAR; }

// void EstadoPato::set_dejar_de_saltar() { estado_salto = BYTE_NULO; }

// void EstadoPato::set_caer() { estado_salto = CAER; }

// void EstadoPato::set_dejar_de_caer() { estado_salto = BYTE_NULO; }
