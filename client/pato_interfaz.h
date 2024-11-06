#ifndef PATO_INTERFAZ_H
#define PATO_INTERFAZ_H

#include <vector>
#include "movimiento_lateral.h"
#include "movimiento_salto.h"
#include "movimiento_agachado.h"
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

class PatoInterfaz {
private:
    MovimientoLateral movimiento_pato_lateral;
    MovimientoSalto movimiento_pato_salto;
    MovimientoAgachado movimiento_pato_agachado;
    std::vector<SDL2pp::Texture> movimiento_pato;
    std::vector<SDL2pp::Texture> salto_pato;
    std::vector<SDL2pp::Texture> acostarse_pato;
    int puntero_movimiento; 

    void frames_movimientos(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    void frames_salto(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    void frames_acostarse(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet);
    void cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet, int offset_y,
                       std::vector<SDL2pp::Texture>& texturas, int num_frames);

    SDL2pp::Texture& mostrar_frame_derecha();

public:
    PatoInterfaz(SDL2pp::Renderer& renderer, const std::string& pato_path);

    void pato_camina_derecha(SDL2pp::Renderer& renderer, SDL_Rect& rect_inicio,
                             SDL2pp::Rect& rect_destino);

    void pato_camina_izquierda(SDL2pp::Renderer& renderer, SDL_Rect& rect_inicio,
                               SDL2pp::Rect& rect_destino);  // Nueva declaración

    void pato_salta(SDL2pp::Renderer& renderer, SDL_Rect& rect_inicio, SDL2pp::Rect& rect_destino);

    void pato_agachado(SDL2pp::Renderer& renderer, SDL_Rect& rect_inicio,
                       SDL2pp::Rect& rect_destino);

    SDL2pp::Texture& mostrar_frame();

    void dibujar(uint8_t& estado_pato_movimiento, uint8_t& estado_pato_salto, uint8_t& direccion_pato, bool se_tira_al_piso, int pos_x, int pos_y, int it);
};

#endif  // PATO_INTERFAZ_H
