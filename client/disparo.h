#ifndef DISPARO_H
#define DISPARO_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>
#include <vector>
#include "../common/common_constantes.h"
#include "movimiento.h"
#include "arma_interfaz.h"
#include "bala_interfaz.h"

class Disparo : public Movimiento {
private:
    SDL2pp::Renderer& renderer;
    ArmaInterfaz arma;
    BalaInterfaz bala;

public:
    Disparo(SDL2pp::Renderer& renderer, const std::string& disparo_path, const std::string& bala_path, int pos_x, int pos_y);  
    void mostrar_disparo(uint8_t& estado_disparo, uint8_t& direccion_pato, int pos_x, int pos_y, float zoom_factor);

    ArmaInterfaz& get_arma();
    BalaInterfaz& get_bala();


};

#endif //DISPARO_H
