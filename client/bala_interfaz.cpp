#include "bala_interfaz.h"

#define CANT_MAX_FRAMES_BALA 8

BalaInterfaz::BalaInterfaz(SDL2pp::Surface& superficie, const std::string& bala_path, 
                                int pos_x, int pos_y, uint8_t direccion) :
        bala_derecha(),
        bala_izquierda(), 
        bala_arriba(),
        rect_inicio_bala(0, 0, PIXEL_BALA, PIXEL_BALA),
        rect_dibujado_bala(pos_x, pos_y, PIXEL_BALA, PIXEL_BALA),
        superficie(superficie), 
        bala_surface(IMG_Load(bala_path.c_str())),
        bala_surface_arriba(IMG_Load(bala_path.c_str())), 
        direccion(direccion) 
{
    cargar_frames(bala_surface, CANT_MAX_FRAMES_BALA, bala_derecha, 0, 0, PIXEL_BALA, PIXEL_BALA);
    flip_horizontal(bala_surface);
    cargar_frames(bala_surface, CANT_MAX_FRAMES_BALA, bala_izquierda, 0, 0, PIXEL_BALA, PIXEL_BALA);
    rotacion_90_grados(bala_surface_arriba);
    cargar_frames(bala_surface_arriba, CANT_MAX_FRAMES_BALA, bala_arriba, 0, 0, PIXEL_BALA, PIXEL_BALA);
}

void BalaInterfaz::set_posicion_bala(uint16_t pos_x_final, uint16_t pos_y_final) {
    rect_dibujado_bala.SetX(pos_x_final);
    rect_dibujado_bala.SetY(pos_y_final); 
}

void BalaInterfaz::dibujar(int it) {
    if(direccion == DIRECCION_DERECHA) {
        SDL_BlitScaled(bala_derecha[it % CANT_MAX_FRAMES_BALA].Get(), nullptr, superficie.Get(), &rect_dibujado_bala);
    } else if (direccion == DIRECCION_IZQUIERDA) {
        SDL_BlitScaled(bala_izquierda[it % CANT_MAX_FRAMES_BALA].Get(), nullptr, superficie.Get(), &rect_dibujado_bala);
    } else if (direccion == DIRECCION_ARRIBA) {
        SDL_BlitScaled(bala_arriba[it % CANT_MAX_FRAMES_BALA].Get(), nullptr, superficie.Get(), &rect_dibujado_bala);
    }
}
