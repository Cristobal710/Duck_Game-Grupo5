#include "movimiento_agachado.h"
#include "../common/common_constantes.h"

#define NUM_FRAMES_PATO_AGACHADO 5
#define PIXEL_PATO 32

MovimientoAgachado::MovimientoAgachado(SDL2pp::Renderer& renderer, const std::string& pato_path, 
int pos_x, int pos_y):
    movimiento_pato_agachado(),
    puntero_agachado_derecha(0),
    puntero_agachado_izquierda(0),
    rect_inicio(1, 8, PIXEL_PATO, PIXEL_PATO),  // Ajusta el valor de `offset_y` a la posición de frames agachado
    rect_dibujado(pos_x, pos_y, PIXEL_PATO, PIXEL_PATO),
    renderer(renderer)
{
    SDL2pp::Surface sprite_pato(IMG_Load(pato_path.c_str()));
    frames_agachado(renderer, sprite_pato);
}

void MovimientoAgachado::frames_agachado(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
    cargar_frames(renderer, sprite_sheet, 70, movimiento_pato_agachado, NUM_FRAMES_PATO_AGACHADO);
}

void MovimientoAgachado::mostrar_frame_agachado(int it) {
    if (it > NUM_FRAMES_PATO_AGACHADO) {
        renderer.Copy(movimiento_pato_agachado[(it % NUM_FRAMES_PATO_AGACHADO)], rect_inicio,
                      rect_dibujado);
        return;
    }
    renderer.Copy(movimiento_pato_agachado[(it)], rect_inicio,
                  rect_dibujado);
}

SDL2pp::Texture& MovimientoAgachado::mostrar_frame() {
    return movimiento_pato_agachado[0];
}

void MovimientoAgachado::pato_agachado(int pos_x, int pos_y, int it){
    rect_dibujado.SetX(pos_x);
    rect_dibujado.SetY(pos_y);
    mostrar_frame_agachado(it);
}

void MovimientoAgachado::cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
                                       int offset_y, std::vector<SDL2pp::Texture>& texturas,
                                       int num_frames) {
    for (int i = 0; i < num_frames; ++i) {
        SDL_Rect rect_inicial = {i * PIXEL_PATO, offset_y, PIXEL_PATO, PIXEL_PATO};
        
        SDL2pp::Surface sprite_superficie(
            SDL_CreateRGBSurface(0, PIXEL_PATO, PIXEL_PATO, 32, 0, 0, 0, 0)
        );
        SDL_BlitSurface(sprite_sheet.Get(), &rect_inicial, sprite_superficie.Get(), nullptr);
        
        Uint32 color_key = SDL_MapRGB(sprite_superficie.Get()->format, 0, 0, 0);
        SDL_SetColorKey(sprite_superficie.Get(), SDL_TRUE, color_key);

        SDL2pp::Texture sprite_textura(renderer, sprite_superficie);
        texturas.emplace_back(std::move(sprite_textura));
    }
}