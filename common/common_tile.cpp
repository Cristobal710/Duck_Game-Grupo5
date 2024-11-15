#include "common_tile.h"

Tile::Tile(uint16_t pos_x, uint16_t pos_y, HitBox hitbox) : pos_x(pos_x), pos_y(pos_y), hitbox(hitbox) {}

HitBox Tile::get_hitbox() {
    return hitbox;
}
