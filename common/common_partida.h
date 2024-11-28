#ifndef COMMON_PARTIDA_H
#define COMMON_PARTIDA_H
#include "common_pato.h"
#include <list>

class Partida {
    private:
    uint8_t id_partida;
    std::list<Pato> jugadores;
    int rondas_jugadas;
    bool partida_iniciada;

    public:
    Partida(uint8_t id_partida);
    void agregar_jugador(uint16_t& id_jugador);
    bool tiene_id(uint8_t id);
    uint8_t obtener_id();
    std::list<Pato>& obtener_jugadores();
    size_t cantidad_jugadores();
};


#endif
