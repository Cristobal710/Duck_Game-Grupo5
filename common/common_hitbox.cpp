#include "common_hitbox.h"

HitBox::HitBox() {}

HitBox::HitBox(uint16_t pos_x, uint16_t pos_y, uint16_t largo, uint16_t ancho) {
    superior_izq = {pos_x, pos_y};
    superior_der = {pos_x + ancho, pos_y};
    inferior_izq = {pos_x, pos_y + largo};
    inferior_der = {pos_x + ancho, pos_y + largo};
}

SDL_Point HitBox::get_superior_izq() { return superior_izq; }

SDL_Point HitBox::get_superior_der() { return superior_der; }

SDL_Point HitBox::get_inferior_izq() { return inferior_izq; }

SDL_Point HitBox::get_inferior_der() { return inferior_der; }

