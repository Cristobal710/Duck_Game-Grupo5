#ifndef MOVIMIENTO_AGACHADO_H
#define MOVIMIENTO_AGACHADO_H

#include <vector>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

class MovimientoAgachado {
    private:
    std::vector<SDL2pp::Texture> movimiento_pato_agachado;
    int puntero_agachado_derecha;
    int puntero_agachado_izquierda;
    SDL2pp::Rect rect_inicio;
    SDL2pp::Rect rect_dibujado;
    SDL2pp::Renderer& renderer;

    void frames_agachado(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    void cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet, int offset_y,
                       std::vector<SDL2pp::Texture>& texturas, int num_frames);
    
    void mostrar_frames_agachado(int it);
    void mostrar_frames_levantarse(int it);
    SDL2pp::Texture& mostrar_frame();

    public:
    MovimientoAgachado(SDL2pp::Renderer& renderer, const std::string& pato_path, int pos_x, int pos_y);
    void pato_agachado(uint8_t& esta_agachado, int pos_x, int pos_y, int it);
};

#endif  // MOVIMIENTO_AGACHADO_H