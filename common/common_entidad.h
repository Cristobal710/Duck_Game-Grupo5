#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <cstdint>
#include "../server/server_hitbox.h"

class Entidad {
protected:
    uint16_t id;
    uint16_t pos_x;
    uint16_t pos_y;
    //HitBox hitbox;

public:
    Entidad();
    Entidad(uint16_t id, uint16_t pos_x, uint16_t pos_y);
    uint16_t get_id();
    uint16_t get_pos_x();
    uint16_t get_pos_y();
    HitBox get_hitbox();
};

#endif
