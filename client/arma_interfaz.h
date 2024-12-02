#ifndef ARMA_INTERFAZ_H
#define ARMA_INTERFAZ_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>
#include <vector>
#include "../common/common_constantes.h"
#include "procesador_sprites.h"

class ArmaInterfaz : public ProcesadorSprites {
private:
    SDL2pp::Surface& superficie;
    SDL2pp::Surface arma_surface;
    SDL2pp::Surface arma_surface_arriba;
    std::vector<SDL2pp::Surface> arma_derecha;
    std::vector<SDL2pp::Surface> arma_izquierda;
    std::vector<SDL2pp::Surface> arma_arriba;
    SDL2pp::Rect rect_inicio_arma;
    SDL2pp::Rect rect_dibujado_arma;
    uint8_t municion_disponible;
    uint16_t id;
    bool recogida;

public:

    ArmaInterfaz(SDL2pp::Surface& superficie, const std::string& arma_path, int pos_x, int pos_y, uint16_t id);
    void dibujar(uint8_t& direccion_pato);
    void no_dibujar();
    void set_municion(uint8_t municion);
    uint8_t get_municion_disponible();
    bool mismo_arma(uint16_t id);
    void set_posicion(int pos_x, int pos_y);
    void soltar();
};


#endif
