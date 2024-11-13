#include "movimiento_salto.h"
#include "../common/common_constantes.h"

#define NUM_FRAMES_SALTA_PATO 3
#define NUM_FRAMES_CAE_PATO 6

MovimientoSalto::MovimientoSalto(SDL2pp::Renderer& renderer, const std::string& pato_path,
                                 int pos_x, int pos_y):
    salto_frames(),
    caida_frames(),
    puntero_salto(0),
    rect_inicio(1, 8, PIXEL_PATO, PIXEL_PATO),
    rect_dibujado(pos_x, pos_y, PIXEL_PATO, PIXEL_PATO),
    renderer(renderer) 
{
    SDL2pp::Surface sprite_pato(IMG_Load(pato_path.c_str()));
    frames_salto(renderer, sprite_pato);
    frames_caida(renderer, sprite_pato);
}

void MovimientoSalto::frames_salto(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
    cargar_frames(renderer, sprite_sheet, 38, salto_frames, NUM_FRAMES_SALTA_PATO);
}

void MovimientoSalto::frames_caida(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
    cargar_frames(renderer, sprite_sheet, 48, caida_frames, NUM_FRAMES_CAE_PATO);
}

void MovimientoSalto::mostrar_frame_salto(int it) {
    renderer.Copy(salto_frames[(it % NUM_FRAMES_SALTA_PATO)], rect_inicio, rect_dibujado);
}

void MovimientoSalto::mostrar_frame_caida(int it) {
    renderer.Copy(caida_frames[(it % NUM_FRAMES_CAE_PATO)], rect_inicio, rect_dibujado);
}

void MovimientoSalto::pato_salta(uint8_t& movimiento, int pos_x, int pos_y, int it, float zoom_factor) {
    set_zoom_in(zoom_factor, rect_dibujado, pos_x, pos_y);

    if (movimiento == SALTAR_ALETEAR) {
        mostrar_frame_salto(it);
        puntero_salto = (puntero_salto + 1) % NUM_FRAMES_SALTA_PATO;
        mostrar_frame_caida(it);
        puntero_caida = (puntero_caida + 1) % NUM_FRAMES_CAE_PATO;
    } 
    // Uncomment if the CAER behavior is needed
    // else if (movimiento == CAER) {
    //    mostrar_frame_caida(it);
    //    puntero_caida = (puntero_caida + 1) % NUM_FRAMES_CAE_PATO;
    // }
}
