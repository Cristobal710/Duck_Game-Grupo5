#ifndef ARMADURA_INTERFAZ_H
#define ARMADURA_INTERFAZ_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>
#include "../common/common_constantes.h"
#include <vector>
#include "procesador_sprites.h"

class ArmaduraInterfaz : public ProcesadorSprites{
private:
    SDL2pp::Surface& superficie;
    SDL2pp::Surface armadura_surface;
    std::vector<SDL2pp::Surface> armadura_derecha;
    std::vector<SDL2pp::Surface> armadura_izquierda;
    SDL2pp::Rect rect_inicio_armadura;
    SDL2pp::Rect rect_dibujado_armadura;

public:
    ArmaduraInterfaz(SDL2pp::Surface&, int pos_x, int pos_y);
    void dibujar(uint8_t& direccion_pato);
    void set_posicion(int pos_x, int pos_y);
};

#endif