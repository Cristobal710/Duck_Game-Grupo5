#include "common_tile.h"

Tile::Tile(uint16_t pos_x, uint16_t pos_y, SDL2pp::Rect hitbox) : pos_x(pos_x), pos_y(pos_y), hitbox(hitbox) {}

SDL2pp::Rect Tile::get_hitbox() {
    return hitbox;
}
