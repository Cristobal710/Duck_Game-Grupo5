#include "movimiento_salto.h"
#include "../common/common_constantes.h"

#define NUM_FRAMES_SALTA_PATO 3
#define NUM_FRAMES_CAE_PATO 2

MovimientoSalto::MovimientoSalto(SDL2pp::Surface& superficie, const std::string& pato_path,
                                 int pos_x, int pos_y, SDL_Color color):
    salto_frames_derecha(),
    salto_frames_izquierda(),
    caida_frames_derecha(),
    caida_frames_izquierda(),
    rect_inicio(0, 0, PIXEL_PATO, PIXEL_PATO),
    rect_dibujado(pos_x, pos_y, PIXEL_PATO, PIXEL_PATO),
    superficie(superficie),
    pato_surface_salto(IMG_Load(pato_path.c_str())),
    pato_surface_caida(IMG_Load(pato_path.c_str())),
    color(color)
{  
    frames_salto(pato_surface_salto);
    frames_caida(pato_surface_caida);
}

void MovimientoSalto::frames_salto(SDL2pp::Surface& sprite_sheet) {
    aplicar_color(sprite_sheet, color);
    cargar_frames(sprite_sheet, NUM_FRAMES_SALTA_PATO, salto_frames_derecha, 38, 1, PIXEL_PATO, PIXEL_PATO);
    FlipSurfaceHorizontally(sprite_sheet);
    cargar_frames(sprite_sheet, NUM_FRAMES_SALTA_PATO, salto_frames_izquierda, 38, 1, PIXEL_PATO, PIXEL_PATO);
}

void MovimientoSalto::frames_caida(SDL2pp::Surface& sprite_sheet) {
    aplicar_color(sprite_sheet, color);
    cargar_frames(sprite_sheet, NUM_FRAMES_CAE_PATO, caida_frames_derecha, 38, 97, PIXEL_PATO, PIXEL_PATO);
    FlipSurfaceHorizontally(sprite_sheet);
    cargar_frames(sprite_sheet, NUM_FRAMES_CAE_PATO, caida_frames_izquierda, 38, 97, PIXEL_PATO, PIXEL_PATO);
}

void MovimientoSalto::mostrar_frame_salto(int it, uint8_t direccion) {
    if(direccion == DIRECCION_DERECHA) {
        SDL_BlitScaled(salto_frames_derecha[(it % NUM_FRAMES_SALTA_PATO)].Get(), nullptr, superficie.Get(), &rect_dibujado);
    } else {
        SDL_BlitScaled(salto_frames_izquierda[(it % NUM_FRAMES_SALTA_PATO)].Get(), nullptr, superficie.Get(), &rect_dibujado);    
    }
}

void MovimientoSalto::mostrar_frame_caida(int it, uint8_t direccion) {
    if(direccion == DIRECCION_DERECHA) {
        SDL_BlitScaled(caida_frames_derecha[it % NUM_FRAMES_CAE_PATO].Get(), nullptr, superficie.Get(), &rect_dibujado);
    } else {
        SDL_BlitScaled(caida_frames_izquierda[it % NUM_FRAMES_CAE_PATO].Get(), nullptr, superficie.Get(), &rect_dibujado);
    }
}

void MovimientoSalto::pato_salta(uint8_t& movimiento, int pos_x, int pos_y, int it, uint8_t direccion) {
    rect_dibujado.SetX(pos_x);
    rect_dibujado.SetY(pos_y);
    
    if (movimiento == SALTAR_ALETEAR) {
        mostrar_frame_salto(it, direccion);
    } else if (movimiento == CAER) {
        mostrar_frame_caida(it, direccion);
    }
}

