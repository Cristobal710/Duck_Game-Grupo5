#include "arma_interfaz.h"

ArmaInterfaz::ArmaInterfaz(SDL2pp::Surface& superficie, const std::string& arma_path, 
                                int pos_x, int pos_y) :
        superficie(superficie),
        arma_surface(IMG_Load(arma_path.c_str())),
        arma_surface_arriba(IMG_Load(arma_path.c_str())),
        arma_derecha(),
        arma_izquierda(),
        arma_arriba(),
        rect_inicio_arma(0, 0, PIXEL_ARMA, PIXEL_ARMA), 
        rect_dibujado_arma(pos_x, pos_y+5, PIXEL_ARMA, PIXEL_ARMA),
        municion_disponible(0)
{   
    cargar_frames(arma_surface, 1, arma_derecha, 0, 0, PIXEL_ARMA, PIXEL_ARMA);
    FlipSurfaceHorizontally(arma_surface);
    cargar_frames(arma_surface, 1, arma_izquierda, 0, 0, PIXEL_ARMA, PIXEL_ARMA);
    RotateSurface90Degrees(arma_surface_arriba);
    cargar_frames(arma_surface_arriba, 1, arma_arriba, 0, 0, PIXEL_ARMA, PIXEL_ARMA);
}

void ArmaInterfaz::set_municion(uint8_t municion) {
    municion_disponible = municion;
}

uint8_t ArmaInterfaz::get_municion_disponible() {
    return municion_disponible;
}

void ArmaInterfaz::set_posicion(int pos_x, int pos_y) {
    rect_dibujado_arma.SetX(pos_x);
    rect_dibujado_arma.SetY(pos_y);
}

void ArmaInterfaz::dibujar(uint8_t& direccion_pato) {
    if (direccion_pato == DIRECCION_DERECHA) {
        SDL_BlitScaled(arma_derecha[0].Get(), nullptr, superficie.Get(), &rect_dibujado_arma);
    } else if (direccion_pato == DIRECCION_IZQUIERDA) {
        SDL_BlitScaled(arma_izquierda[0].Get(), nullptr, superficie.Get(), &rect_dibujado_arma);
    } else if (direccion_pato == DIRECCION_ARRIBA) {
        SDL_BlitScaled(arma_arriba[0].Get(), nullptr, superficie.Get(), &rect_dibujado_arma);
    }
}

