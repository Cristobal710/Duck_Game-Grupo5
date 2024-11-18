#ifndef MOVIMIENTO_LATERAL_H
#define MOVIMIENTO_LATERAL_H

#include <vector>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "movimiento.h"

class MovimientoLateral : public Movimiento {
    private:
    std::vector<SDL2pp::Texture> movimiento_pato;
    int puntero_movimiento_derecha;
    int puntero_movimiento_izquierda;
    SDL2pp::Rect rect_inicio;
    SDL2pp::Rect rect_dibujado;
    SDL2pp::Renderer& renderer;
    SDL_Color color;

    void frames_movimientos(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
   
    void mostrar_frame_derecha(int it);
    void mostrar_frame_izquierda(int it);
    void mostrar_frame(uint8_t& direccion_pato);

    public:
    MovimientoLateral(SDL2pp::Renderer& renderer, const std::string& pato_path, int pos_x, int pos_y, SDL_Color color);
    void pato_movimiento(uint8_t& movimiento, uint8_t& direccion_pato, int& pos_x, int& pos_y, int it, float zoom_factor);
};



#endif
