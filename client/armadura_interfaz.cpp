#include "armadura_interfaz.h"

#define PIXEL_ARMADURA 16

ArmaduraInterfaz::ArmaduraInterfaz(SDL2pp::Surface& superficie, int pos_x, int pos_y) :
        superficie(superficie),
        armadura_surface(IMG_Load("../resources/armors/chestPlatePickup.png")),
        armadura_derecha(),
        armadura_izquierda(),
        rect_inicio_armadura(0, 0, PIXEL_ARMADURA, PIXEL_ARMADURA),
        rect_dibujado_armadura((pos_x+10), (pos_y+15), PIXEL_ARMADURA, PIXEL_ARMADURA)
{
    cargar_frames(armadura_surface, 1, armadura_derecha, 0, 0, PIXEL_ARMADURA, PIXEL_ARMADURA);
    FlipSurfaceHorizontally(armadura_surface);
    cargar_frames(armadura_surface, 1, armadura_izquierda, 0, 0, PIXEL_ARMADURA, PIXEL_ARMADURA);
}

void ArmaduraInterfaz::dibujar(uint8_t& direccion_pato) {
    if (direccion_pato == DIRECCION_DERECHA) {
        SDL_BlitScaled(armadura_derecha[0].Get(), nullptr, superficie.Get(), &rect_dibujado_armadura);
    } else {
        SDL_BlitScaled(armadura_izquierda[0].Get(), nullptr, superficie.Get(), &rect_dibujado_armadura);    
    }
}


