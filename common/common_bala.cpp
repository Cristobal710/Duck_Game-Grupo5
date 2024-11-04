#include "common_bala.h"

Bala::Bala(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint16_t pos_x_final, uint16_t pos_y_final,
           uint8_t direccion):
        Entidad(id, pos_x, pos_y),
        pos_x_final(pos_x_final),
        pos_y_final(pos_y_final),
        direccion(direccion) {}

uint16_t Bala::get_pos_x_final() { return pos_x_final; }

uint16_t Bala::get_pos_y_final() { return pos_y_final; }

uint8_t Bala::get_direccion() { return direccion; }