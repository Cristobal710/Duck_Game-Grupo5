#include "disparo.h"

#define NUM_FRAMES_DISPARO 3
#define PIXEL_DISPARO 32

Disparo::Disparo(SDL2pp::Renderer& renderer, const std::string& disparo_path, int pos_x, int pos_y)
    : disparo(), 
      puntero_disparo(0), 
      rect_inicio(0, 0, PIXEL_DISPARO, PIXEL_DISPARO), 
      rect_dibujado(pos_x, pos_y, PIXEL_DISPARO, PIXEL_DISPARO), 
      renderer(renderer)
{
    SDL2pp::Surface sprite_disparo(IMG_Load(disparo_path.c_str()));
    frames_disparo(renderer, sprite_disparo);
}

void Disparo::frames_disparo(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
    cargar_frames(renderer, sprite_sheet, 21, disparo, NUM_FRAMES_DISPARO, 2);
}

void Disparo::mostrar_frame_dart(uint8_t& direccion_pato, int it) {
    if(direccion_pato == DIRECCION_DERECHA) {
        if (it > NUM_FRAMES_DISPARO) {
            renderer.Copy(disparo[(it % NUM_FRAMES_DISPARO)], rect_inicio, rect_dibujado);
        } else {
            renderer.Copy(disparo[it], rect_inicio, rect_dibujado);
        }
    } else {
        if (it > NUM_FRAMES_DISPARO) {
            SDL_RenderCopyEx(renderer.Get(), disparo[(it % NUM_FRAMES_DISPARO)].Get(), &rect_inicio, &rect_dibujado, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);
        } else {
            SDL_RenderCopyEx(renderer.Get(), disparo[it].Get(), &rect_inicio, &rect_dibujado, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);
        }
    }
}

void Disparo::mostrar_frame_gun(uint8_t& direccion_pato, int it) {
    if (it > NUM_FRAMES_DISPARO) {
        if(direccion_pato == DIRECCION_DERECHA) {
            renderer.Copy(disparo[0], rect_inicio, rect_dibujado);
        } else {
            SDL_RenderCopyEx(renderer.Get(), disparo[0].Get(), &rect_inicio, &rect_dibujado, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);
        }
    } else {
        if(direccion_pato == DIRECCION_DERECHA) {
            renderer.Copy(disparo[0], rect_inicio, rect_dibujado);
        } else {
            SDL_RenderCopyEx(renderer.Get(), disparo[0].Get(), &rect_inicio, &rect_dibujado, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);
        }
    }
}

void Disparo::mostrar_disparo(uint8_t& estado_disparo, uint8_t& direccion_pato, int pos_x, int pos_y, int it) {
    rect_dibujado.SetX(pos_x);
    rect_dibujado.SetY(pos_y);

    if (estado_disparo == DISPARAR) {
        mostrar_frame_dart(direccion_pato, it);
    } else {
        mostrar_frame_gun(direccion_pato, it);
    }
}

void Disparo::cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
                   int offset_y, std::vector<SDL2pp::Texture>& texturas,
                   int num_frames, int offset_x) {
    for (int i = 0; i < num_frames; ++i) {

        SDL_Rect rect_inicial = {i * PIXEL_DISPARO + offset_x, offset_y, PIXEL_DISPARO, PIXEL_DISPARO};

        SDL2pp::Surface sprite_superficie(
                SDL_CreateRGBSurface(0, PIXEL_DISPARO, PIXEL_DISPARO, 32, 0, 0, 0, 0));

        SDL_BlitSurface(sprite_sheet.Get(), &rect_inicial, sprite_superficie.Get(), nullptr);

        Uint32 color_key = SDL_MapRGB(sprite_superficie.Get()->format, 0, 0, 0);
        SDL_SetColorKey(sprite_superficie.Get(), SDL_TRUE, color_key);

        SDL2pp::Texture sprite_textura(renderer, sprite_superficie);

        texturas.emplace_back(std::move(sprite_textura));
    }
}
