#ifndef HITBOX_H
#define HITBOX_H

#include <SDL2/SDL.h>
#include <cstdint>

class HitBox{
    public:
    HitBox(uint16_t x, uint16_t y, uint16_t largo, uint16_t ancho);
    SDL_Point superior_izq;
    SDL_Point superior_der;
    SDL_Point inferior_izq;
    SDL_Point inferior_der;
};

#endif