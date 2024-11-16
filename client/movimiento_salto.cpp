#include "movimiento_salto.h"
#include "../common/common_constantes.h"

#define NUM_FRAMES_SALTA_PATO 3
#define NUM_FRAMES_CAE_PATO 3

MovimientoSalto::MovimientoSalto(SDL2pp::Renderer& renderer, const std::string& pato_path,
                                 int pos_x, int pos_y):
    salto_frames(),
    caida_frames(),
    puntero_salto(0),
    rect_inicio(0, 0, PIXEL_PATO, PIXEL_PATO),
    rect_dibujado(pos_x, pos_y, PIXEL_PATO, PIXEL_PATO),
    renderer(renderer) 
{
    SDL2pp::Surface sprite_pato(IMG_Load(pato_path.c_str()));
    frames_salto(renderer, sprite_pato);
    frames_caida(renderer, sprite_pato);
}

void MovimientoSalto::frames_salto(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
    cargar_frames(renderer, sprite_sheet, 38, salto_frames, NUM_FRAMES_SALTA_PATO, 1, PIXEL_PATO, PIXEL_PATO);
}

void MovimientoSalto::frames_caida(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
    cargar_frames(renderer, sprite_sheet, 38, caida_frames, NUM_FRAMES_CAE_PATO, 97, PIXEL_PATO, PIXEL_PATO);
}

void MovimientoSalto::mostrar_frame_salto(int it) {
    renderer.Copy(salto_frames[(it % NUM_FRAMES_SALTA_PATO)], rect_inicio, rect_dibujado);
}

void MovimientoSalto::mostrar_frame_caida(int it) {
    renderer.Copy(caida_frames[(it % NUM_FRAMES_CAE_PATO)], rect_inicio, rect_dibujado);
}

void MovimientoSalto::pato_salta(uint8_t& movimiento, int pos_x, int pos_y, int it, float zoom_factor) {
    set_zoom_in(zoom_factor, rect_dibujado, pos_x, pos_y);

    if (movimiento == SALTAR_ALETEAR) {
        mostrar_frame_salto(it);
    } else if (movimiento == CAER) {
        mostrar_frame_caida(it);
    }
}

void MovimientoSalto::cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
                   int offset_y, std::vector<SDL2pp::Texture>& texturas,
                   int num_frames, int offset_x, int pixeles_x, int pixeles_y) {
    for (int i = 0; i < num_frames; ++i) {

        SDL_Rect rect_inicial = {i * pixeles_x + offset_x, offset_y, pixeles_x, pixeles_y};

        SDL2pp::Surface sprite_superficie(
                SDL_CreateRGBSurface(0, pixeles_x, pixeles_y, 32, 0, 0, 0, 0));

        SDL_BlitSurface(sprite_sheet.Get(), &rect_inicial, sprite_superficie.Get(), nullptr);

        Uint32 color_key = SDL_MapRGB(sprite_superficie.Get()->format, 0, 0, 0);
        SDL_SetColorKey(sprite_superficie.Get(), SDL_TRUE, color_key);

        SDL2pp::Texture sprite_textura(renderer, sprite_superficie);

        texturas.emplace_back(std::move(sprite_textura));
    }
}
