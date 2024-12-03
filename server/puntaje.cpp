#include "puntaje.h"


Puntaje::Puntaje(uint16_t id) :
id_jugador(id), rondas_ganadas(0)
{}

bool Puntaje::tengo_id(uint16_t un_id) { return (un_id == id_jugador); }

void Puntaje::gana_una_ronda() {
    rondas_ganadas = rondas_ganadas + 2;
}

int Puntaje::get_puntaje() { return rondas_ganadas; }

bool Puntaje::gano_la_partida() { 
    if (rondas_ganadas >= 10){
        return true;
    }
    return false;
}
