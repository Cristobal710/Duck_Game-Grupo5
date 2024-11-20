#ifndef CASCO_INTERFAZ_H
#define CASCO_INTERFAZ_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>
#include "../common/common_constantes.h"
#include "procesador_sprites.h"

class CascoInterfaz : public ProcesadorSprites {
private:
    SDL2pp::Surface& superficie;
    SDL2pp::Surface casco_surface;
    std::vector<SDL2pp::Surface> casco_derecha;
    std::vector<SDL2pp::Surface> casco_izquierda;
    SDL2pp::Rect rect_inicio_casco;
    SDL2pp::Rect rect_dibujado_casco;

public:
    CascoInterfaz(SDL2pp::Surface& superficie, int pos_x, int pos_y);
    void dibujar(uint8_t& direccion_pato);
    void set_posicion(int pos_x, int pos_y);

};

#endif
