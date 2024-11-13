#include "disparo.h"

#include "arma_interfaz.h"

#define NUM_FRAMES_DISPARO 3
#define PIXEL_DISPARO 32
#define PIXEL_BALA_X 36
#define PIXEL_BALA_Y 20

Disparo::Disparo(SDL2pp::Renderer& renderer, const std::string& disparo_path, const std::string& bala_path, int pos_x, int pos_y)
    :renderer(renderer),
    arma(renderer, disparo_path, pos_x, pos_y),
    bala(renderer, bala_path, pos_x, pos_y)
{}

ArmaInterfaz& Disparo::get_arma() { return arma; }

BalaInterfaz& Disparo::get_bala() { return bala; }


void Disparo::mostrar_disparo(uint8_t& estado_disparo, uint8_t& direccion_pato, int pos_x, int pos_y, float zoom_factor) {
    arma.set_posicion(pos_x, pos_y, zoom_factor);

    if ((estado_disparo == DISPARAR) && (arma.get_municion_disponible() > 0)) {
        arma.mostrar_frame_arma(direccion_pato);
        bala.mostrar_frame_bala(direccion_pato);
    } else {
        arma.mostrar_frame_arma(direccion_pato);
    }
}
