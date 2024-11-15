#ifndef HITBOX_H
#define HITBOX_H

#include <SDL2/SDL.h>
#include <cstdint>

class HitBox {
    public:
        HitBox();
        HitBox(uint16_t pos_x, uint16_t pos_y, uint16_t largo, uint16_t ancho);
        SDL_Point superior_izq;
        SDL_Point superior_der;
        SDL_Point inferior_izq;
        SDL_Point inferior_der;
        SDL_Point get_superior_izq();
        SDL_Point get_superior_der();
        SDL_Point get_inferior_izq();
        SDL_Point get_inferior_der();
        bool colisiona_arriba_con(HitBox hitbox);
        bool colisiona_abajo_con(HitBox hitbox);
        bool colisiona_izquierda_con(HitBox hitbox);
        bool colisiona_derecha_con(HitBox hitbox);
};

#endif