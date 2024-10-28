#ifndef BALA_H
#define BALA_H

#include "common_entidad.h"

class Bala: public Entidad {
protected:
    uint8_t pos_x_final;
    uint8_t pos_y_final;
    uint8_t direccion;

public:
    Bala(uint8_t id, uint8_t pos_x, uint8_t pos_y, uint8_t pos_x_final, uint8_t pos_y_final, uint8_t direccion);
    uint8_t get_pos_x_final();
    uint8_t get_pos_y_final();
    uint8_t get_direccion();
};

#endif
