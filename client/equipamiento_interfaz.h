#ifndef EQUIPAMIENTO_INTERFAZ_H
#define EQUIPAMIENTO_INTERFAZ_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>
#include <vector>
#include "../common/common_constantes.h"
#include "procesador_sprites.h"

class EquipamientoInterfaz : public ProcesadorSprites {
private:
    SDL2pp::Surface& superficie;
    SDL2pp::Surface equipamiento_surface;
    std::vector<SDL2pp::Surface> equipamiento;
    SDL2pp::Rect rect_inicio_equipamiento;
    SDL2pp::Rect rect_dibujado_equipamiento;

public:

    EquipamientoInterfaz(SDL2pp::Surface& superficie, const std::string& equipamiento_path, int pos_x, int pos_y);
    void dibujar();

};

#endif
