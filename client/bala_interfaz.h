#ifndef BALA_INTERFAZ_H
#define BALA_INTERFAZ_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>
#include <vector>
#include "../common/common_constantes.h"
#include "procesador_sprites.h"

class BalaInterfaz : public ProcesadorSprites {
private:
    std::vector<SDL2pp::Surface> bala_derecha;
    std::vector<SDL2pp::Surface> bala_izquierda;
    std::vector<SDL2pp::Surface> bala_arriba;
    SDL2pp::Rect rect_inicio_bala;
    SDL2pp::Rect rect_dibujado_bala;
    SDL2pp::Surface& superficie;
    SDL2pp::Surface bala_surface;
    SDL2pp::Surface bala_surface_arriba;
    uint8_t direccion;


public:
    BalaInterfaz(SDL2pp::Surface& superficie, const std::string& bala_path, int pos_x, int pos_y, uint8_t direccion);
    void dibujar(int it);

    void set_posicion_bala(uint16_t pos_x_final, uint16_t pos_y_final);

};

#endif