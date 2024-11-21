#include "movimiento_salto.h"
#include "../common/common_constantes.h"

#define NUM_FRAMES_SALTA_PATO 3
#define NUM_FRAMES_CAE_PATO 2
#define NUM_FRAMES_ALETEA_PATO 3

MovimientoSalto::MovimientoSalto(SDL2pp::Surface& superficie, const std::string& pato_path,
                                 int pos_x, int pos_y, SDL_Color color):
    salto_frames_derecha(),
    salto_frames_izquierda(),
    caida_frames_derecha(),
    caida_frames_izquierda(),
    aleteo_frames_derecha(),
    aleteo_frames_izquierda(),
    rect_inicio(0, 0, PIXEL_PATO, PIXEL_PATO),
    rect_dibujado(pos_x, pos_y, PIXEL_PATO, PIXEL_PATO),
    superficie(superficie),
    pato_surface_salto(IMG_Load(pato_path.c_str())),
    pato_surface_caida(IMG_Load(pato_path.c_str())),
    pato_surface_aleteo(IMG_Load(pato_path.c_str())),
    color(color)
{  
    guardar_frames(pato_surface_salto, NUM_FRAMES_SALTA_PATO, salto_frames_derecha, salto_frames_izquierda, 1, 40, color);
    guardar_frames(pato_surface_caida, NUM_FRAMES_CAE_PATO, caida_frames_derecha, caida_frames_izquierda, 97, 40, color);
    guardar_frames(pato_surface_aleteo, NUM_FRAMES_ALETEA_PATO, aleteo_frames_derecha, aleteo_frames_izquierda, 33, 40, color);
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

void MovimientoSalto::mostrar_frame_aleteo(int it, uint8_t direccion) {
    if(direccion == DIRECCION_DERECHA) {
        SDL_BlitScaled(salto_frames_derecha[it % NUM_FRAMES_ALETEA_PATO].Get(), nullptr, superficie.Get(), &rect_dibujado);
    } else {
        SDL_BlitScaled(salto_frames_izquierda[it % NUM_FRAMES_ALETEA_PATO].Get(), nullptr, superficie.Get(), &rect_dibujado);    
    }
}

void MovimientoSalto::pato_salta(uint8_t& movimiento, int pos_x, int pos_y, int it, uint8_t direccion) {
    rect_dibujado.SetX(pos_x);
    rect_dibujado.SetY(pos_y);
    
    if (movimiento == SALTAR) {
        mostrar_frame_salto(it, direccion);
    } else if (movimiento == CAER) {
        mostrar_frame_caida(it, direccion);
    } else if (movimiento == ALETEAR) {
        mostrar_frame_aleteo(it, direccion);
    }
}

