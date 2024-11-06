#ifndef ESTADO_PATO_H
#define ESTADO_PATO_H

#include <cstdint>
#include "common_constantes.h"

class EstadoPato {
    private:
        uint8_t estado_movimiento;
        uint8_t estado_salto;
        uint8_t estado_agachado;
    public:
        EstadoPato();
        EstadoPato(uint8_t estado_movimiento, uint8_t estado_salto, uint8_t estado_agachado);
        //EstadoPato(uint8_t estado_movimiento);
        uint8_t get_estado_movimiento();
        uint8_t get_estado_salto();
        uint8_t get_estado_agachado();
        void set_moviendo_derecha();
        void set_moviendo_izquierda();
        void set_dejar_de_moverse();
        void set_saltar();
        void set_dejar_de_saltar();
        void set_caer();
        void set_dejar_de_caer();
        void set_agacharse();
        void set_dejar_de_agacharse();
};

#endif