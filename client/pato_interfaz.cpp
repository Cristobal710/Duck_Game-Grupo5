#include "pato_interfaz.h"

#include "../common/common_constantes.h"
#include <SDL2/SDL_image.h>

#define NUM_FRAMES_MOVIMIENTO_PATO 6
#define NUM_FRAMES_SALTA_PATO 3
#define NUM_FRAMES_BAJA_PATO 6
#define NUM_FRAMES_PATO_ACOSTADO 5
#define PIXEL_PATO 32

PatoInterfaz::PatoInterfaz(SDL2pp::Renderer& renderer, const std::string& pato_path):
    movimiento_pato_lateral(renderer, pato_path, 150, 150),
    movimiento_pato_salto(renderer, pato_path, 150, 150),
    movimiento_pato_agachado(renderer, pato_path, 150, 150)
{
    SDL2pp::Surface sprite_pato(IMG_Load(pato_path.c_str()));
    
    frames_movimientos(renderer, sprite_pato);
    frames_salto(renderer, sprite_pato);
    frames_acostarse(renderer, sprite_pato);
    puntero_movimiento = 0;
}

void PatoInterfaz::pato_camina_derecha(SDL2pp::Renderer& renderer, SDL_Rect& rect_inicio,
                                       SDL2pp::Rect& rect_destino) {
    for (int i = 0; i < NUM_FRAMES_MOVIMIENTO_PATO; ++i) {
        renderer.Clear();
        //rect_destino.x += 2;
        renderer.Copy(movimiento_pato[i], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio),
                      SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
        renderer.Present();
        SDL_Delay(70);
    }
    renderer.Copy(movimiento_pato[0], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio),
                  SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
    renderer.Present();
}

void PatoInterfaz::pato_camina_izquierda(SDL2pp::Renderer& renderer, SDL_Rect& rect_inicio,
                                         SDL2pp::Rect& rect_destino) {
    for (int i = 0; i < NUM_FRAMES_MOVIMIENTO_PATO; ++i) {
        renderer.Clear();
        rect_destino.x -= 2;
        SDL_RenderCopyEx(renderer.Get(), movimiento_pato[i].Get(), &rect_inicio, &rect_destino, 0,
                         nullptr, SDL_FLIP_HORIZONTAL);
        renderer.Present();
        SDL_Delay(70);
    }
    SDL_RenderCopyEx(renderer.Get(), movimiento_pato[0].Get(), &rect_inicio, &rect_destino, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);
    renderer.Present();
}

void PatoInterfaz::pato_salta(SDL2pp::Renderer& renderer, SDL_Rect& rect_inicio,
                              SDL2pp::Rect& rect_destino) {
    for (int i = 0; i < NUM_FRAMES_SALTA_PATO; ++i) {
        renderer.Clear();
        rect_destino.y -= 3;
        rect_destino.x += 0.5;
        renderer.Copy(salto_pato[i], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio),
                      SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
        renderer.Present();
        SDL_Delay(70);
    }

    for (int i = 3; i < NUM_FRAMES_BAJA_PATO; ++i) {
        renderer.Clear();
        rect_destino.y += 1;
        rect_destino.x += 0.5;
        renderer.Copy(salto_pato[i], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio),
                      SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
        renderer.Present();
        SDL_Delay(70);
    }

    renderer.Copy(salto_pato[0], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio),
                  SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
    renderer.Present();
}

void PatoInterfaz::pato_agachado(SDL2pp::Renderer& renderer, SDL_Rect& rect_inicio,
                                 SDL2pp::Rect& rect_destino) {
    for (int i = 0; i < NUM_FRAMES_PATO_ACOSTADO; ++i) {
        renderer.Clear();
        renderer.Copy(acostarse_pato[i], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio),
                      SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
        renderer.Present();
        SDL_Delay(150);
    }
    renderer.Clear();
    renderer.Copy(acostarse_pato[0], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio),
                  SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
    renderer.Present();
}

SDL2pp::Texture& PatoInterfaz::mostrar_frame() { return movimiento_pato[0]; }

void PatoInterfaz::dibujar(uint8_t& estado_pato_movimiento, uint8_t& estado_pato_salto, uint8_t& direccion_pato, uint8_t& se_tira_al_piso, int pos_x, int pos_y, int it) {
    if(se_tira_al_piso == TIRAR_PISO){
        movimiento_pato_agachado.pato_agachado(se_tira_al_piso, pos_x, pos_y, it);
        return;
    } else if (estado_pato_salto == SALTAR_ALETEAR || estado_pato_salto == CAER) {
        movimiento_pato_salto.pato_salta(estado_pato_salto, pos_x, pos_y, it);
        return;
    } 
    movimiento_pato_lateral.pato_movimiento(estado_pato_movimiento, direccion_pato, pos_x, pos_y, it);
}

SDL2pp::Texture& PatoInterfaz::mostrar_frame_derecha(){
    return movimiento_pato[puntero_movimiento];
}


void PatoInterfaz::frames_movimientos(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
    cargar_frames(renderer, sprite_sheet, 6, movimiento_pato, NUM_FRAMES_MOVIMIENTO_PATO);
}

void PatoInterfaz::frames_salto(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
    cargar_frames(renderer, sprite_sheet, 38, salto_pato, NUM_FRAMES_MOVIMIENTO_PATO);
}

void PatoInterfaz::frames_acostarse(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
    cargar_frames(renderer, sprite_sheet, 70, acostarse_pato, NUM_FRAMES_PATO_ACOSTADO);
}

void PatoInterfaz::cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
                                 int offset_y, std::vector<SDL2pp::Texture>& texturas,
                                 int num_frames) {
    for (int i = 0; i < num_frames; ++i) {

        SDL_Rect rect_inicial = {i * PIXEL_PATO, offset_y, PIXEL_PATO, PIXEL_PATO};

        SDL2pp::Surface sprite_superficie(
                SDL_CreateRGBSurface(0, PIXEL_PATO, PIXEL_PATO, 32, 0, 0, 0, 0));

        SDL_BlitSurface(sprite_sheet.Get(), &rect_inicial, sprite_superficie.Get(), nullptr);

        Uint32 color_key = SDL_MapRGB(sprite_superficie.Get()->format, 0, 0, 0);

        SDL_SetColorKey(sprite_superficie.Get(), SDL_TRUE, color_key);

        SDL2pp::Texture sprite_textura(renderer, sprite_superficie);

        texturas.emplace_back(std::move(sprite_textura));
    }
}
