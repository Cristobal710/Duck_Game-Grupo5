#include "common_hitbox.h"

HitBox::HitBox() {}

HitBox::HitBox(uint16_t pos_x, uint16_t pos_y, uint16_t largo, uint16_t ancho) {
    hitbox_rect = SDL2pp::Rect(pos_x, pos_y, largo, ancho);
}

SDL2pp::Rect HitBox::get_hitbox_rect() {
    return hitbox_rect;
}

// bool HitBox::colisiona_arriba_con(const HitBox& hitbox) {
//     return (hitbox.inferior_izq.y == superior_izq.y) &&
//            (superior_izq.x <= hitbox.superior_der.x || superior_der.x >= hitbox.superior_izq.x);
// }

// bool HitBox::colisiona_abajo_con(const HitBox& hitbox) {
//     return (hitbox.inferior_izq.y == inferior_der.y) &&
//            (superior_izq.x <= hitbox.superior_der.x || superior_der.x >= hitbox.superior_izq.x);
// }

// bool HitBox::colisiona_izquierda_con(const HitBox& hitbox) {
//     return (hitbox.superior_izq.x == superior_der.x) &&
//            (superior_izq.y <= hitbox.superior_der.y || inferior_izq.y >= hitbox.superior_izq.y);
// }

// bool HitBox::colisiona_derecha_con(const HitBox& hitbox) {
//     return (hitbox.superior_der.x == superior_izq.x) &&
//            (superior_izq.y <= hitbox.superior_der.y || inferior_izq.y >= hitbox.superior_der.y); 
// }
