#ifndef BALA_H
#define BALA_H

#include "common_entidad.h"

class Bala: public Entidad {
protected:
    uint16_t pos_x_final;
    uint16_t pos_y_final;
    uint8_t direccion;

public:
    Bala(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint16_t pos_x_final, uint16_t pos_y_final,
         uint8_t direccion);
    uint16_t get_pos_x_final();
    uint16_t get_pos_y_final();
    uint8_t get_direccion();
};

#endif
