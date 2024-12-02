#ifndef COMMON_PARTIDA_H
#define COMMON_PARTIDA_H
#include "common_pato.h"
#include <list>

class Partida {
    private:
    uint8_t id_partida;
    std::list<uint16_t> jugadores;
    int rondas_jugadas;
    bool partida_iniciada;
    int cant_jugadores;
    uint16_t id_creador;

    public:
    Partida(uint8_t id_partida);
    void agregar_jugador(uint16_t id_jugador);
    void agregar_creador(uint16_t id);
    bool tiene_id(uint8_t id);
    uint8_t obtener_id();
    std::list<uint16_t>& obtener_jugadores();
    size_t cantidad_jugadores();

    void set_cant_jugadores(int cant);
    int get_cant_jugadores();

    void iniciar();
    bool esta_iniciada();
};


#endif
