#include "common_explosion.h"

Explosion::Explosion(uint8_t id, uint8_t pos_x, uint8_t pos_y, uint8_t pos_x_final, uint8_t pos_y_final) : Entidad(id, pos_x, pos_y), pos_x_final(pos_x_final), pos_y_final(pos_y_final) {}

uint8_t Explosion::get_pos_x_final() {
    return pos_x_final;
}

uint8_t Explosion::get_pos_y_final() {
    return pos_y_final;
}