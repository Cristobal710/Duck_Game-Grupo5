#include "movimiento_lateral.h"

#define NUM_FRAMES_MOVIMIENTO_PATO 6

MovimientoLateral::MovimientoLateral(SDL2pp::Surface& superficie, const std::string& pato_path, 
int pos_x, int pos_y, SDL_Color color)
    : movimiento_pato_derecha(),
    movimiento_pato_izquierda(),
    rect_inicio(1, 8, PIXEL_PATO, PIXEL_PATO),
    rect_dibujado(pos_x, pos_y, PIXEL_PATO, PIXEL_PATO),
    pato_surface(IMG_Load(pato_path.c_str())),
    superficie(superficie),
    color(color)
{
    frames_movimientos(pato_surface);
}

void MovimientoLateral::frames_movimientos(SDL2pp::Surface& sprite_sheet) {
    aplicar_color(sprite_sheet, color);
    cargar_frames(sprite_sheet, NUM_FRAMES_MOVIMIENTO_PATO, movimiento_pato_derecha, 7, 1, PIXEL_PATO, PIXEL_PATO);
    flip_horizontal(sprite_sheet);
    cargar_frames(sprite_sheet, NUM_FRAMES_MOVIMIENTO_PATO, movimiento_pato_izquierda, 7, 1, PIXEL_PATO, PIXEL_PATO);    
}

void MovimientoLateral::mostrar_frame_derecha(int it) {
    SDL_BlitScaled(movimiento_pato_derecha[it % NUM_FRAMES_MOVIMIENTO_PATO].Get(), nullptr, superficie.Get(), &rect_dibujado);
}

void MovimientoLateral::mostrar_frame_izquierda(int it) {
    SDL_BlitScaled(movimiento_pato_izquierda[it % NUM_FRAMES_MOVIMIENTO_PATO].Get(), nullptr, superficie.Get(), &rect_dibujado);
}

void MovimientoLateral::mostrar_frame(uint8_t& direccion_pato) { 
    if (direccion_pato == DIRECCION_DERECHA){
        SDL_BlitScaled(movimiento_pato_derecha[0].Get(), nullptr, superficie.Get(), &rect_dibujado);
    } else if (direccion_pato == DIRECCION_IZQUIERDA) {
        SDL_BlitScaled(movimiento_pato_izquierda[0].Get(), nullptr, superficie.Get(), &rect_dibujado);
    }
}

void MovimientoLateral::pato_movimiento(uint8_t& movimiento, uint8_t& direccion_pato, int pos_x, int pos_y, int it) {
    rect_dibujado.SetX(pos_x);
    rect_dibujado.SetY(pos_y);

    if (movimiento == MOVER_DERECHA) {
        mostrar_frame_derecha(it);
    } else if (movimiento == MOVER_IZQUIERDA) {
        mostrar_frame_izquierda(it);
    } else {
        mostrar_frame(direccion_pato);
    } 
}

