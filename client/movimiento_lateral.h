#ifndef MOVIMIENTO_LATERAL_H
#define MOVIMIENTO_LATERAL_H

#include <vector>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>


class MovimientoLateral {
    private:
    std::vector<SDL2pp::Texture> movimiento_pato;
    int puntero_movimiento_derecha;
    int puntero_movimiento_izquierda;
    SDL2pp::Rect rect_inicio;
    SDL2pp::Rect rect_dibujado;
    SDL2pp::Renderer& renderer;

    void frames_movimientos(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    void cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet, int offset_y,
                       std::vector<SDL2pp::Texture>& texturas, int num_frames);
    
    void mostrar_frame_derecha();
    void mostrar_frame_izquierda();
    SDL2pp::Texture& mostrar_frame();

    public:
    MovimientoLateral(SDL2pp::Renderer& renderer, const std::string& pato_path, int pos_x, int pos_y);
    void pato_movimiento(std::string& movimiento, int pos_x, int pos_y);
};



#endif
