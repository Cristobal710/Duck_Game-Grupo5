#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <cstdint>

class Entidad {
protected:
    uint8_t id;
    uint8_t pos_x;
    uint8_t pos_y;

public:
    Entidad(uint8_t id, uint8_t pos_x, uint8_t pos_y);
    uint8_t get_id();
    uint8_t get_pos_x();
    uint8_t get_pos_y();
};

#endif
