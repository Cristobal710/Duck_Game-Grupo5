#ifndef MOVIMIENTO_SALTO_H
#define MOVIMIENTO_SALTO_H

#include <vector>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "procesador_sprites.h"

class MovimientoSalto : public ProcesadorSprites {
private:
    std::vector<SDL2pp::Surface> salto_frames_derecha;
    std::vector<SDL2pp::Surface> salto_frames_izquierda;
    std::vector<SDL2pp::Surface> caida_frames_derecha;
    std::vector<SDL2pp::Surface> caida_frames_izquierda;
    std::vector<SDL2pp::Surface> aleteo_frames_derecha;
    std::vector<SDL2pp::Surface> aleteo_frames_izquierda;
    SDL2pp::Rect rect_inicio;
    SDL2pp::Rect rect_dibujado;
    SDL2pp::Surface& superficie;
    SDL2pp::Surface pato_surface_salto;
    SDL2pp::Surface pato_surface_caida;
    SDL2pp::Surface pato_surface_aleteo;
    SDL_Color color;
    
    void mostrar_frame_salto(int it, uint8_t direccion);
    void mostrar_frame_caida(int it, uint8_t direccion);
    void mostrar_frame_aleteo(int it, uint8_t direccion);

public:
    MovimientoSalto(SDL2pp::Surface& superficie, const std::string& pato_path, int pos_x, int pos_y, SDL_Color color);
    void pato_salta(uint8_t& movimiento, int pos_x, int pos_y, int it, uint8_t direccion);
};

#endif