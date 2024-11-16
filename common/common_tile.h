#ifndef COMMMON_TILE_H
#define COMMON_TILE_H
#include <string>
#include "common_hitbox.h"
#include <SDL2pp/SDL2pp.hh>

class Tile {
    public:
        uint16_t pos_x;
        uint16_t pos_y;
        SDL2pp::Rect hitbox;
        Tile(uint16_t pos_x, uint16_t pos_y, SDL2pp::Rect hitbox);
        SDL2pp::Rect get_hitbox();
};

#endif