#include "casco_interfaz.h"

#define PIXEL_CASCO 16

CascoInterfaz::CascoInterfaz(SDL2pp::Surface& superficie, int pos_x, int pos_y)
    : superficie(superficie),
    casco_surface(IMG_Load("../resources/armors/knightHelmet.png")),
    casco_derecha(),
    casco_izquierda(),
    rect_inicio_casco(0, 0, PIXEL_CASCO, PIXEL_CASCO),
    rect_dibujado_casco((pos_x+10), (pos_y), PIXEL_CASCO, PIXEL_CASCO)
{
    cargar_frames(casco_surface, 1, casco_derecha, 0, 0, PIXEL_CASCO, PIXEL_CASCO);
    flip_horizontal(casco_surface);
    cargar_frames(casco_surface, 1, casco_izquierda, 0, 0, PIXEL_CASCO, PIXEL_CASCO);
}

void CascoInterfaz::dibujar(uint8_t& direccion_pato) {    
    if (direccion_pato == DIRECCION_DERECHA) {
        SDL_BlitScaled(casco_derecha[0].Get(), nullptr, superficie.Get(), &rect_dibujado_casco);
    } else {
        SDL_BlitScaled(casco_izquierda[0].Get(), nullptr, superficie.Get(), &rect_dibujado_casco);
    }  
}
