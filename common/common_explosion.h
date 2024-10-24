#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "common_entidad.h"

class Explosion : public Entidad {
    protected:
        uint8_t pos_x_final;
        uint8_t pos_y_final;
    public:
        Explosion(uint8_t id, uint8_t pos_x, uint8_t pos_y, uint8_t pos_x_final, uint8_t pos_y_final);
        uint8_t get_pos_x_final();
        uint8_t get_pos_y_final();
};

#endif