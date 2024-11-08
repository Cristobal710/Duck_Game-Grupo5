#ifndef DISPARO_H
#define DISPARO_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>
#include <vector>
#include "../common/common_constantes.h"

class Disparo {
private:
    std::vector<SDL2pp::Texture> disparo;
    int puntero_disparo;
    SDL2pp::Rect rect_inicio;
    SDL2pp::Rect rect_dibujado;
    SDL2pp::Renderer& renderer;
    
    void frames_disparo(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    void mostrar_frame_dart(uint8_t& direccion_pato, int it);
    void mostrar_frame_gun(uint8_t& direccion_pato, int it);
    void cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet, int offset_y, std::vector<SDL2pp::Texture>& texturas, int num_frames, int offset_x);

public:
    Disparo(SDL2pp::Renderer& renderer, const std::string& disparo_path, int pos_x, int pos_y);  
    void mostrar_disparo(uint8_t& estado_disparo, uint8_t& direccion_pato, int pos_x, int pos_y, int it);

};

#endif //DISPARO_H
