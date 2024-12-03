#include "puntaje.h"


Puntaje::Puntaje(uint16_t id) :
id_jugador(id), rondas_ganadas(0)
{}

bool Puntaje::tengo_id(uint16_t un_id) { return (un_id == id_jugador); }

void Puntaje::gana_una_ronda() {
    rondas_ganadas = rondas_ganadas + 1;
}

int Puntaje::get_puntaje() { return rondas_ganadas; }
