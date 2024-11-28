#include "common_partida.h"


Partida::Partida(uint8_t id_partida):
id_partida(id_partida),jugadores(), rondas_jugadas(0), partida_iniciada(false)
{}

void Partida::agregar_jugador(uint16_t& id_jugador) {
    Pato nuevo_pato(id_jugador, 100, 100, DIRECCION_DERECHA);
    jugadores.emplace_front(nuevo_pato);
}

bool Partida::tiene_id(uint8_t id) { 
    return (id == id_partida); 
    }

uint8_t Partida::obtener_id() { return id_partida; }

std::list<Pato>& Partida::obtener_jugadores() {
    return jugadores;
}

size_t Partida::cantidad_jugadores() { return jugadores.size(); }
