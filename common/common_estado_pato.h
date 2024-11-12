#ifndef ESTADO_PATO_H
#define ESTADO_PATO_H

#include <cstdint>
#include "common_constantes.h"

class EstadoPato {
    private:
        uint8_t estado_movimiento;
        uint8_t estado_salto;
        uint8_t estado_agachado;
        uint8_t estado_disparo;

    public:
        EstadoPato();
        EstadoPato(uint8_t estado_movimiento, uint8_t estado_salto, uint8_t estado_agachado, uint8_t estado_disparo);
        //EstadoPato(uint8_t estado_movimiento);
        uint8_t get_estado_movimiento();
        uint8_t get_estado_salto();
        uint8_t get_estado_agachado();
        uint8_t get_estado_disparo();
        void set_moviendo_derecha();
        void set_moviendo_izquierda();
        void set_dejar_de_moverse();
        void set_saltar();
        void set_dejar_de_saltar();
        void set_caer();
        void set_dejar_de_caer();
        void set_agacharse();
        void set_dejar_de_agacharse();
        void set_disparando();
        void set_dejar_de_disparar();
};

#endif