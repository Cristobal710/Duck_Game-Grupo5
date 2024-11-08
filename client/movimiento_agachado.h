#ifndef MOVIMIENTO_AGACHADO_H
#define MOVIMIENTO_AGACHADO_H

#include <vector>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "movimiento.h"

class MovimientoAgachado : public Movimiento {
    private:
    std::vector<SDL2pp::Texture> movimiento_pato_agachado;
    int puntero_agachado_derecha;
    int puntero_agachado_izquierda;
    SDL2pp::Rect rect_inicio;
    SDL2pp::Rect rect_dibujado;
    SDL2pp::Renderer& renderer;

    void frames_agachado(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    
    void mostrar_frames_agachado(int it);
    void mostrar_frames_levantarse(int it);
    SDL2pp::Texture& mostrar_frame();

    public:
    MovimientoAgachado(SDL2pp::Renderer& renderer, const std::string& pato_path, int pos_x, int pos_y);
    void pato_agachado(uint8_t& esta_agachado, int pos_x, int pos_y, int it);
};

#endif  // MOVIMIENTO_AGACHADO_H