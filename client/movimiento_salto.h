#ifndef MOVIMIENTO_SALTO_H
#define MOVIMIENTO_SALTO_H

#include <vector>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "movimiento.h"

class MovimientoSalto : public Movimiento {
private:
    std::vector<SDL2pp::Texture> salto_frames;
    std::vector<SDL2pp::Texture> caida_frames;
    int puntero_salto;
    int puntero_caida;
    SDL2pp::Rect rect_inicio;
    SDL2pp::Rect rect_dibujado;
    SDL2pp::Renderer& renderer;

    void frames_salto(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    void frames_caida(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    
    void mostrar_frame_salto(int it);
    void mostrar_frame_caida(int it);

public:
    MovimientoSalto(SDL2pp::Renderer& renderer, const std::string& pato_path, int pos_x, int pos_y);
    void pato_salta(uint8_t& movimiento, int& pos_x, int& pos_y, int it, float zoom_factor);
};

#endif