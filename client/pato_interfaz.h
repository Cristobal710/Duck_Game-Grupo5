#ifndef PATO_INTERFAZ_H
#define PATO_INTERFAZ_H

#include <vector>
#include "movimiento_lateral.h"
#include "movimiento_salto.h"
#include "movimiento_agachado.h"
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

class PatoInterfaz {
private:
    MovimientoLateral movimiento_pato_lateral;
    MovimientoSalto movimiento_pato_salto;
    MovimientoAgachado movimiento_pato_agachado;

public:
    PatoInterfaz(SDL2pp::Renderer& renderer, const std::string& pato_path);

    void dibujar(uint8_t& estado_pato_movimiento, uint8_t& estado_pato_salto, uint8_t& direccion_pato, uint8_t& se_tira_al_piso, int pos_x, int pos_y, int it);

};

#endif  // PATO_INTERFAZ_H
