#include "common_estado_pato.h"

EstadoPato::EstadoPato():
        estado_movimiento(BYTE_NULO),
        estado_salto(BYTE_NULO),
        estado_agachado(BYTE_NULO),
        estado_disparo(BYTE_NULO) {}

EstadoPato::EstadoPato(uint8_t estado_movimiento, uint8_t estado_salto, uint8_t estado_agachado, uint8_t estado_disparo):
        estado_movimiento(estado_movimiento),
        estado_salto(estado_salto),
        estado_agachado(estado_agachado),
        estado_disparo(estado_disparo) {}

uint8_t EstadoPato::get_estado_movimiento() { return estado_movimiento; }

uint8_t EstadoPato::get_estado_salto() { return estado_salto; }

uint8_t EstadoPato::get_estado_agachado() { return estado_agachado; }

uint8_t EstadoPato::get_estado_disparo() { return estado_disparo; }

void EstadoPato::set_disparando(){ estado_disparo = DISPARAR; }

void EstadoPato::set_dejar_de_disparar(){ estado_disparo = BYTE_NULO; }

void EstadoPato::set_moviendo_derecha() { estado_movimiento = MOVER_DERECHA; }

void EstadoPato::set_moviendo_izquierda() { estado_movimiento = MOVER_IZQUIERDA; }

void EstadoPato::set_dejar_de_moverse() { estado_movimiento = BYTE_NULO; }

void EstadoPato::set_saltar() { estado_salto = SALTAR; }

void EstadoPato::set_dejar_de_saltar() { estado_salto = BYTE_NULO; }

void EstadoPato::set_aletear() { estado_salto = ALETEAR; }

void EstadoPato::set_dejar_de_aletear() { estado_salto = BYTE_NULO; }

void EstadoPato::set_caer() { estado_salto = CAER; }

void EstadoPato::set_dejar_de_caer() { estado_salto = BYTE_NULO; }

void EstadoPato::set_agacharse() { estado_agachado = TIRAR_PISO; }

void EstadoPato::set_dejar_de_agacharse() { estado_agachado = BYTE_NULO; }