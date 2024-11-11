#include "movimiento_agachado.h"
#include "../common/common_constantes.h"

#define NUM_FRAMES_PATO_AGACHADO 5
#define PIXEL_PATO 32

MovimientoAgachado::MovimientoAgachado(SDL2pp::Renderer& renderer, const std::string& pato_path, 
int pos_x, int pos_y):
    movimiento_pato_agachado(),
    puntero_agachado_derecha(0),
    puntero_agachado_izquierda(0),
    rect_inicio(1, 8, PIXEL_PATO, PIXEL_PATO),
    rect_dibujado(pos_x, pos_y, PIXEL_PATO, PIXEL_PATO),
    renderer(renderer)
{
    SDL2pp::Surface sprite_pato(IMG_Load(pato_path.c_str()));
    frames_agachado(renderer, sprite_pato);
}

void MovimientoAgachado::frames_agachado(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
    cargar_frames(renderer, sprite_sheet, 70, movimiento_pato_agachado, NUM_FRAMES_PATO_AGACHADO);
}

void MovimientoAgachado::mostrar_frames_agachado(int it) {
    int frame = NUM_FRAMES_PATO_AGACHADO - 1 - (it % NUM_FRAMES_PATO_AGACHADO);

    if (it > NUM_FRAMES_PATO_AGACHADO) {
        renderer.Copy(movimiento_pato_agachado[0], rect_inicio, rect_dibujado);
        return;
    }
    renderer.Copy(movimiento_pato_agachado[frame], rect_inicio, rect_dibujado);
}

void MovimientoAgachado::mostrar_frames_levantarse(int it) {
    int frame = it % NUM_FRAMES_PATO_AGACHADO;

    if (it > NUM_FRAMES_PATO_AGACHADO) {
        renderer.Copy(movimiento_pato_agachado[NUM_FRAMES_PATO_AGACHADO - 1], rect_inicio, rect_dibujado);
        return;
    }
    renderer.Copy(movimiento_pato_agachado[frame], rect_inicio, rect_dibujado);
}

SDL2pp::Texture& MovimientoAgachado::mostrar_frame() {
    return movimiento_pato_agachado[0];
}

void MovimientoAgachado::pato_agachado(uint8_t& esta_agachado, int& pos_x, int& pos_y, int it, float zoom_factor) {
    set_zoom_in(zoom_factor, rect_dibujado, pos_x, pos_y);

    if (esta_agachado == TIRAR_PISO) {
        mostrar_frames_agachado(it);
    } else {
        mostrar_frames_levantarse(it);
    }
}
