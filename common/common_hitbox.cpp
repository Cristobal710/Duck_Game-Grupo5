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

bool HitBox::colisiona_arriba_con(HitBox hitbox) {
    return (superior_izq.x < hitbox.inferior_izq.x && superior_der.x > hitbox.inferior_izq.x) &&
           (superior_izq.y < hitbox.inferior_izq.y && superior_der.y < hitbox.inferior_izq.y);
}

bool HitBox::colisiona_abajo_con(HitBox hitbox) {
    return (inferior_izq.x < hitbox.superior_izq.x && inferior_der.x > hitbox.superior_izq.x) &&
           (inferior_izq.y > hitbox.superior_izq.y && inferior_der.y > hitbox.superior_izq.y);
}

bool HitBox::colisiona_izquierda_con(HitBox hitbox) {
    return (superior_izq.x < hitbox.superior_der.x && inferior_izq.x < hitbox.superior_der.x) &&
           (superior_izq.y < hitbox.superior_der.y && inferior_izq.y > hitbox.superior_izq.y);
}

bool HitBox::colisiona_derecha_con(HitBox hitbox) {
    return (superior_der.x > hitbox.superior_izq.x && inferior_der.x > hitbox.superior_izq.x) &&
           (superior_der.y < hitbox.superior_der.y && inferior_der.y > hitbox.superior_izq.y);
}
