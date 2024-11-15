#ifndef COMMMON_TILE_H
#define COMMON_TILE_H
#include <string>
#include "common_hitbox.h"
class Tile {
    public:
        uint16_t pos_x;
        uint16_t pos_y;
        HitBox hitbox;
        Tile(uint16_t pos_x, uint16_t pos_y, HitBox hitbox);
        HitBox get_hitbox();
};

#endif