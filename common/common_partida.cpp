#include "common_partida.h"


Partida::Partida(uint8_t id_partida):
id_partida(id_partida), jugadores(), rondas_jugadas(0), 
partida_iniciada(false), cant_jugadores(0), id_creador(0)
{}

void Partida::agregar_jugador(uint16_t id_jugador) {
    //Pato nuevo_pato(id_jugador, 100, 100, DIRECCION_DERECHA);
    //jugadores.emplace_front(nuevo_pato);
    jugadores.emplace_back(id_jugador);
    cant_jugadores++;
}

void Partida::agregar_creador(uint16_t id) {
    id_creador = id;
}

bool Partida::tiene_id(uint8_t id) { 
    return (id == id_partida); 
    }

uint8_t Partida::obtener_id() { return id_partida; }

std::list<uint16_t>& Partida::obtener_jugadores() {
    return jugadores;
}

size_t Partida::cantidad_jugadores() { return jugadores.size(); }

void Partida::set_cant_jugadores(int cant) {
    cant_jugadores = cant;
}

int Partida::get_cant_jugadores() {
    return cant_jugadores;
}

void Partida::iniciar() {
    partida_iniciada = true;
}

bool Partida::esta_iniciada() {
    return partida_iniciada;
}
