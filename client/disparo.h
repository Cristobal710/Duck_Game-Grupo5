#ifndef DISPARO_H
#define DISPARO_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>
#include <vector>
#include "../common/common_constantes.h"

class Disparo {
private:
    std::vector<SDL2pp::Texture> arma;
    std::vector<SDL2pp::Texture> bala;
    SDL2pp::Rect rect_inicio_arma;
    SDL2pp::Rect rect_dibujado_arma;
    SDL2pp::Rect rect_inicio_bala;
    SDL2pp::Rect rect_dibujado_bala;
    SDL2pp::Renderer& renderer;
    int velocidad_bala;
    
    void frames_disparo(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    void frames_bala(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    void mostrar_frame_bala(uint8_t& direccion_pato, int it);
    void mostrar_frame_arma(uint8_t& direccion_pato);
    void cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet, int offset_y, std::vector<SDL2pp::Texture>& texturas, int num_frames, int offset_x, int pixeles_x, int pixeles_y);
    void reiniciar_bala(int pos_x, int pos_y);

public:
    Disparo(SDL2pp::Renderer& renderer, const std::string& disparo_path, const std::string& bala_path, int pos_x, int pos_y);  
    void mostrar_disparo(uint8_t& estado_disparo, uint8_t& direccion_pato, int pos_x, int pos_y, int it);

};

#endif //DISPARO_H
