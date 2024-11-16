#ifndef HITBOX_H
#define HITBOX_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <cstdint>

class HitBox {
    public:
        HitBox();
        HitBox(uint16_t pos_x, uint16_t pos_y, uint16_t largo, uint16_t ancho);
        
        SDL2pp::Rect hitbox_rect;
        SDL2pp::Rect get_hitbox_rect();
        bool no_colisiona(const SDL2pp::Rect hitbox);
        bool colisiona_arriba_con(const SDL2pp::Rect hitbox);
        bool colisiona_abajo_con(const SDL2pp::Rect hitbox);
        bool colisiona_izquierda_con(const SDL2pp::Rect hitbox);
        bool colisiona_derecha_con(const SDL2pp::Rect hitbox);
        int calcular_minima_superposicion(SDL2pp::Rect hitbox_entidad);
};

#endif