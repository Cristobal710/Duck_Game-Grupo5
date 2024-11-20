#ifndef MOVIMIENTO_AGACHADO_H
#define MOVIMIENTO_AGACHADO_H

#include <vector>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "movimiento.h"

class MovimientoAgachado : public Movimiento {
    private:
    std::vector<SDL2pp::Surface> movimiento_pato_agachado_derecha;
    std::vector<SDL2pp::Surface> movimiento_pato_agachado_izquierda;
    SDL2pp::Rect rect_inicio;
    SDL2pp::Rect rect_dibujado;
    SDL2pp::Surface pato_surface;
    SDL2pp::Surface& superficie;
    SDL_Color color;

    void frames_agachado(SDL2pp::Surface& sprite_sheet);
    
    void mostrar_frames_agachado(uint8_t direccion_pato);
    void mostrar_frames_levantarse(int it);
    
    public:
    MovimientoAgachado(SDL2pp::Surface& superficie, const std::string& pato_path, int pos_x, int pos_y, SDL_Color color);
    void pato_agachado(uint8_t& esta_agachado, int pos_x, int pos_y, uint8_t direccion_pato);
    void mostrar_muerte(int pos_x, int pos_y, uint8_t direccion_pato);
};

#endif  // MOVIMIENTO_AGACHADO_H