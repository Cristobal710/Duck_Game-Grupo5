#ifndef PATO_INTERFAZ_H
#define PATO_INTERFAZ_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>
#include <vector>

class PatoInterfaz {
private:
    std::vector<SDL2pp::Texture> movimiento_pato;
    std::vector<SDL2pp::Texture> salto_pato;
    std::vector<SDL2pp::Texture> acostarse_pato;

    void frames_movimientos(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    void frames_salto(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    void frames_acostarse(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    void cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet, int offset_y, std::vector<SDL2pp::Texture>& texturas, int num_frames);

public:
    PatoInterfaz(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    
    void pato_camina_derecha(SDL2pp::Renderer& renderer, SDL_Rect& rect_inicio, SDL2pp::Rect& rect_destino);
    
    void pato_camina_izquierda(SDL2pp::Renderer& renderer, SDL_Rect& rect_inicio, SDL2pp::Rect& rect_destino); // Nueva declaración
    
    void pato_salta(SDL2pp::Renderer& renderer, SDL_Rect& rect_inicio, SDL2pp::Rect& rect_destino);
    
    void pato_agachado(SDL2pp::Renderer& renderer, SDL_Rect& rect_inicio, SDL2pp::Rect& rect_destino);
    
    SDL2pp::Texture& mostrar_frame();
    
    void dibujar(SDL2pp::Renderer& renderer, SDL_Rect& rect_inicio, SDL2pp::Rect& rect_destino);

};

#endif // PATO_INTERFAZ_H



