#include "movimiento_lateral.h"
#include "../common/common_constantes.h"

#define NUM_FRAMES_MOVIMIENTO_PATO 6
#define PIXEL_PATO 32


MovimientoLateral::MovimientoLateral(SDL2pp::Renderer& renderer, const std::string& pato_path, 
int pos_x, int pos_y):
movimiento_pato(),
puntero_movimiento_derecha(0),
puntero_movimiento_izquierda(0),
rect_inicio(1, 8, PIXEL_PATO, PIXEL_PATO),
rect_dibujado(pos_x, pos_y, PIXEL_PATO, PIXEL_PATO),
renderer(renderer) 
{
    SDL2pp::Surface sprite_pato(IMG_Load(pato_path.c_str()));
    frames_movimientos(renderer, sprite_pato);
}


void MovimientoLateral::frames_movimientos(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
        cargar_frames(renderer, sprite_sheet, 6, movimiento_pato, NUM_FRAMES_MOVIMIENTO_PATO);                                           
    }


void MovimientoLateral::mostrar_frame_derecha(int it) {
    renderer.Copy(movimiento_pato[(it % NUM_FRAMES_MOVIMIENTO_PATO)], rect_inicio,
        rect_dibujado);
}

void MovimientoLateral::mostrar_frame_izquierda(int it) {
    SDL_RenderCopyEx(renderer.Get(), movimiento_pato[it % NUM_FRAMES_MOVIMIENTO_PATO].Get(), &rect_inicio, &rect_dibujado, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);
}

void MovimientoLateral::mostrar_frame(uint8_t& direccion_pato) { 
    if (direccion_pato == DIRECCION_DERECHA){
        renderer.Copy(movimiento_pato[0], rect_inicio,
        rect_dibujado);
    } else if (direccion_pato == DIRECCION_IZQUIERDA) {
        SDL_RenderCopyEx(renderer.Get(), movimiento_pato[0].Get(), &rect_inicio, &rect_dibujado, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);
    }
}

void MovimientoLateral::pato_movimiento(uint8_t& movimiento, uint8_t& direccion_pato, int& nueva_pos_x, int& nueva_pos_y, int it, float zoom_factor) {

    rect_dibujado.SetX(nueva_pos_x);
    set_zoom_in(zoom_factor, rect_dibujado, nueva_pos_x, nueva_pos_y);
    
    if (movimiento == MOVER_DERECHA) {
        mostrar_frame_derecha(it);
    } else if (movimiento == MOVER_IZQUIERDA) {
        mostrar_frame_izquierda(it);
    } else {
        mostrar_frame(direccion_pato);
    } 
}

