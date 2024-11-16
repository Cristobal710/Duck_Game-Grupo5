#include "common_hitbox.h"

HitBox::HitBox() {}

HitBox::HitBox(uint16_t pos_x, uint16_t pos_y, uint16_t largo, uint16_t ancho) {
    hitbox_rect = SDL2pp::Rect(pos_x, pos_y, largo, ancho);
}

SDL2pp::Rect HitBox::get_hitbox_rect() {
    return hitbox_rect;
}

int HitBox::calcular_minima_superposicion(SDL2pp::Rect hitbox_entidad) {
    int superpos_der = hitbox_entidad.GetX() + hitbox_entidad.GetW() - hitbox_rect.GetX();
    int superpos_izq = hitbox_rect.GetX() + hitbox_rect.GetW() - hitbox_entidad.GetX();
    int superpos_abajo = hitbox_entidad.GetY() + hitbox_entidad.GetH() - hitbox_rect.GetY();
    int superpos_arriba = hitbox_rect.GetY() + hitbox_rect.GetH() - hitbox_entidad.GetY();

    return std::min({superpos_izq, superpos_der, superpos_arriba, superpos_abajo});
}

bool HitBox::colisiona_arriba_con(const SDL2pp::Rect hitbox_entidad) {
    int superpos_arriba = hitbox_rect.GetY() + hitbox_rect.GetH() - hitbox_entidad.GetY();
    int min_superposicion = calcular_minima_superposicion(hitbox_entidad);
    return (min_superposicion == superpos_arriba);
}

bool HitBox::colisiona_abajo_con(const SDL2pp::Rect hitbox_entidad) {
    int superpos_abajo = hitbox_entidad.GetY() + hitbox_entidad.GetH() - hitbox_rect.GetY();
    int min_superposicion = calcular_minima_superposicion(hitbox_entidad);
    return (min_superposicion == superpos_abajo);
}

bool HitBox::colisiona_izquierda_con(const SDL2pp::Rect hitbox_entidad) {
    int superpos_izq = hitbox_rect.GetX() + hitbox_rect.GetW() - hitbox_entidad.GetX();
    int min_superposicion = calcular_minima_superposicion(hitbox_entidad);
    return (min_superposicion == superpos_izq);
}

bool HitBox::colisiona_derecha_con(const SDL2pp::Rect hitbox_entidad) {
    int superpos_der = hitbox_entidad.GetX() + hitbox_entidad.GetW() - hitbox_rect.GetX();
    int min_superposicion = calcular_minima_superposicion(hitbox_entidad);
    return (min_superposicion == superpos_der);
}

bool HitBox::no_colisiona(const SDL2pp::Rect hitbox_entidad) {
    return !hitbox_rect.Intersects(hitbox_entidad);
}
