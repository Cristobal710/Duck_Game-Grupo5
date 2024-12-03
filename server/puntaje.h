#ifndef PUNTAJE_H
#define PUNTAJE_H
#include <cstdint>

class Puntaje {
    private:
    uint16_t id_jugador;
    int rondas_ganadas;

    public:
    Puntaje(uint16_t id);
    bool tengo_id(uint16_t un_id);
    void gana_una_ronda();
    int get_puntaje();
};


#endif
