#include "movimiento_agachado.h"
#include "../common/common_constantes.h"

#define NUM_FRAMES_PATO_AGACHADO 5

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

void MovimientoAgachado::mostrar_frames_agachado(uint8_t direccion_pato) {
    if (direccion_pato == DIRECCION_DERECHA){
        renderer.Copy(movimiento_pato_agachado[1], rect_inicio, rect_dibujado);
        return;
    } else if (direccion_pato == DIRECCION_IZQUIERDA){
    SDL_RenderCopyEx(renderer.Get(), movimiento_pato_agachado[1].Get(), &rect_inicio, &rect_dibujado, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);
    }
}

void MovimientoAgachado::mostrar_frames_levantarse(int it) {
    int frame = it % NUM_FRAMES_PATO_AGACHADO;

    if (frame == 0){
        renderer.Copy(movimiento_pato_agachado[frame + 2], rect_inicio, rect_dibujado);
        return;
    }
    if (frame == 1){
        renderer.Copy(movimiento_pato_agachado[frame + 1], rect_inicio, rect_dibujado);
        return;
    }
    renderer.Copy(movimiento_pato_agachado[frame], rect_inicio, rect_dibujado);
}

SDL2pp::Texture& MovimientoAgachado::mostrar_frame() {
    return movimiento_pato_agachado[0];
}

void MovimientoAgachado::pato_agachado(uint8_t& esta_agachado, int& pos_x, int& pos_y, float zoom_factor,
uint8_t direccion_pato) {
    set_zoom_in(zoom_factor, rect_dibujado, pos_x, pos_y);
    std::cout << static_cast<int>(esta_agachado) << std::endl;
    if (esta_agachado == TIRAR_PISO) {
        mostrar_frames_agachado(direccion_pato);
        //std::cout << "me agacho" << std::endl;
    } else if (esta_agachado == DEJAR_TIRAR_PISO) {
        mostrar_frames_levantarse(direccion_pato);
        std::cout << "me levanto" << std::endl;
    } 
}
