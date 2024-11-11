#include "pato_interfaz.h"

#include "../common/common_constantes.h"
#include <SDL2/SDL_image.h>

#define PIXEL_PATO 32

PatoInterfaz::PatoInterfaz(SDL2pp::Renderer& renderer, const std::string& pato_path):
    movimiento_pato_lateral(renderer, pato_path, 150, 150),
    movimiento_pato_salto(renderer, pato_path, 150, 150),
    movimiento_pato_agachado(renderer, pato_path, 150, 150)
{}

void PatoInterfaz::dibujar(uint8_t& estado_pato_movimiento, uint8_t& estado_pato_salto, uint8_t& direccion_pato, uint8_t& se_tira_al_piso, int pos_x, int pos_y, int it, float zoom_factor) {
    if(se_tira_al_piso == TIRAR_PISO){
        movimiento_pato_agachado.pato_agachado(se_tira_al_piso, pos_x, pos_y, it, zoom_factor);
        return;
    } else if (estado_pato_salto == SALTAR_ALETEAR || estado_pato_salto == CAER) {
        movimiento_pato_salto.pato_salta(estado_pato_salto, pos_x, pos_y, it, zoom_factor);
        return;
    } 
    movimiento_pato_lateral.pato_movimiento(estado_pato_movimiento, direccion_pato, pos_x, pos_y, it, zoom_factor);
}
