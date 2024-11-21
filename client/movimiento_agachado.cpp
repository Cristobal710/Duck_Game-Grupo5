#include "movimiento_agachado.h"

#define NUM_FRAMES_PATO_AGACHADO 5

MovimientoAgachado::MovimientoAgachado(SDL2pp::Surface& superficie, const std::string& pato_path, 
int pos_x, int pos_y, SDL_Color color):
    movimiento_pato_agachado_derecha(),
    movimiento_pato_agachado_izquierda(),
    rect_inicio(1, 8, PIXEL_PATO, PIXEL_PATO),
    rect_dibujado(pos_x, pos_y, PIXEL_PATO, PIXEL_PATO),
    pato_surface(IMG_Load(pato_path.c_str())),
    superficie(superficie),
    color(color)
{
    guardar_frames(pato_surface, NUM_FRAMES_PATO_AGACHADO, movimiento_pato_agachado_derecha, movimiento_pato_agachado_izquierda, 0, 71, color);
}

void MovimientoAgachado::mostrar_frames_agachado(uint8_t direccion_pato) {
    if (direccion_pato == DIRECCION_DERECHA){
        SDL_BlitScaled(movimiento_pato_agachado_derecha[1].Get(), nullptr, superficie.Get(), &rect_dibujado);
    } else if (direccion_pato == DIRECCION_IZQUIERDA){
        SDL_BlitScaled(movimiento_pato_agachado_izquierda[4].Get(), nullptr, superficie.Get(), &rect_dibujado);
    }
}

void MovimientoAgachado::mostrar_frames_levantarse(int it) {
    int frame = it % NUM_FRAMES_PATO_AGACHADO;

    if (frame == 0){
        SDL_BlitScaled(movimiento_pato_agachado_derecha[frame + 2].Get(), nullptr, superficie.Get(), &rect_dibujado);
        return;
    }
    if (frame == 1){
        SDL_BlitScaled(movimiento_pato_agachado_derecha[frame + 1].Get(), nullptr, superficie.Get(), &rect_dibujado);
        return;
    }
    SDL_BlitScaled(movimiento_pato_agachado_derecha[frame].Get(), nullptr, superficie.Get(), &rect_dibujado);
}

void MovimientoAgachado::mostrar_muerte(int pos_x, int pos_y, uint8_t direccion_pato) {
    rect_dibujado.SetX(pos_x);
    rect_dibujado.SetY(pos_y);

    SDL2pp::Surface tumba(IMG_Load("../resources/grave.png"));
    SDL_BlitScaled(tumba.Get(), nullptr, superficie.Get(), &rect_dibujado);
    
    if (direccion_pato == DIRECCION_DERECHA){
        SDL_BlitScaled(movimiento_pato_agachado_derecha[1].Get(), nullptr, superficie.Get(), &rect_dibujado);
        return;
    } else {
        SDL_BlitScaled(movimiento_pato_agachado_izquierda[4].Get(), nullptr, superficie.Get(), &rect_dibujado);
    }
}

void MovimientoAgachado::pato_agachado(uint8_t& esta_agachado, int pos_x, int pos_y, uint8_t direccion_pato) {
    rect_dibujado.SetX(pos_x);
    rect_dibujado.SetY(pos_y);

    if (esta_agachado == TIRAR_PISO) {
        mostrar_frames_agachado(direccion_pato);
    } else if (esta_agachado == DEJAR_TIRAR_PISO) {
        mostrar_frames_levantarse(direccion_pato);
    } 
}
