#ifndef ARMA_INTERFAZ_H
#define ARMA_INTERFAZ_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>
#include <vector>
#include "../common/common_constantes.h"

class ArmaInterfaz {
private:
    SDL2pp::Renderer& renderer;
    std::vector<SDL2pp::Texture> arma;
    SDL2pp::Rect rect_inicio_arma;
    SDL2pp::Rect rect_dibujado_arma;
    uint8_t municion_disponible;

    void cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
                   int offset_y, std::vector<SDL2pp::Texture>& texturas,
                   int num_frames, int offset_x, int pixeles_x, int pixeles_y);
    void set_zoom_in(float& zoom_factor, SDL2pp::Rect& rect_dibujado, int& pos_x, int& pos_y);

public:

    ArmaInterfaz(SDL2pp::Renderer& renderer, const std::string& arma_path, int pos_x, int pos_y);
    void dibujar(uint8_t& direccion_pato, float& zoom_factor);
    
    void set_municion(uint8_t municion);
    uint8_t get_municion_disponible();
    void set_posicion(int pos_x, int pos_y, float& zoom_factor);

};


#endif