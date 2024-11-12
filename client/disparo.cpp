#include "disparo.h"

#define NUM_FRAMES_DISPARO 3
#define PIXEL_DISPARO 32
#define PIXEL_BALA_X 36
#define PIXEL_BALA_Y 20

Disparo::Disparo(SDL2pp::Renderer& renderer, const std::string& disparo_path, const std::string& bala_path, int pos_x, int pos_y)
    : arma(), 
      bala(), 
      rect_inicio_arma(0, 0, PIXEL_DISPARO, PIXEL_DISPARO), 
      rect_dibujado_arma(pos_x, pos_y, PIXEL_DISPARO, PIXEL_DISPARO), 
      rect_inicio_bala(0, 0, PIXEL_BALA_X, PIXEL_BALA_Y),
      rect_dibujado_bala(pos_x, pos_y, PIXEL_BALA_X, PIXEL_BALA_Y),
      renderer(renderer),
      velocidad_bala(5)
{
    SDL2pp::Surface sprite_disparo(IMG_Load(disparo_path.c_str()));
    SDL2pp::Surface sprite_bala(IMG_Load(bala_path.c_str()));
    frames_disparo(renderer, sprite_disparo);
    frames_bala(renderer, sprite_bala); 
}

void Disparo::frames_disparo(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
    cargar_frames(renderer, sprite_sheet, 21, arma, NUM_FRAMES_DISPARO, 2, PIXEL_DISPARO, PIXEL_DISPARO);
}

void Disparo::frames_bala(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
    cargar_frames(renderer, sprite_sheet, 22, bala, NUM_FRAMES_DISPARO, 83, PIXEL_BALA_X, PIXEL_BALA_Y);
}

void Disparo::mostrar_frame_bala(uint8_t& direccion_pato, int it) {
    mostrar_frame_arma(direccion_pato);
    if(direccion_pato == DIRECCION_DERECHA) {
        if (it > NUM_FRAMES_DISPARO) {
            renderer.Copy(bala[(it % NUM_FRAMES_DISPARO)], rect_inicio_bala, rect_dibujado_bala);
        } else {
            renderer.Copy(bala[it], rect_inicio_bala, rect_dibujado_bala);
        }
    } else {
        if (it > NUM_FRAMES_DISPARO) {
            SDL_RenderCopyEx(renderer.Get(), bala[(it % NUM_FRAMES_DISPARO)].Get(), &rect_inicio_bala, &rect_dibujado_bala, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);
        } else {
            SDL_RenderCopyEx(renderer.Get(), bala[it].Get(), &rect_inicio_bala, &rect_dibujado_bala, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);
        }
    }
}

void Disparo::mostrar_frame_arma(uint8_t& direccion_pato) {
    if (direccion_pato == DIRECCION_DERECHA) {
        renderer.Copy(arma[0], rect_inicio_arma, rect_dibujado_arma);
    } else {
        SDL_RenderCopyEx(renderer.Get(), arma[0].Get(), &rect_inicio_arma, &rect_dibujado_arma, 0, nullptr, SDL_FLIP_HORIZONTAL);
    }
}

void Disparo::mostrar_disparo(uint8_t& estado_disparo, uint8_t& direccion_pato, int pos_x, int pos_y, int it, float zoom_factor) {
    rect_dibujado_arma.SetX(pos_x);
    rect_dibujado_arma.SetY(pos_y);

    rect_dibujado_bala.SetX(pos_x);
    rect_dibujado_bala.SetY(pos_y);

    set_zoom_in(zoom_factor, rect_dibujado_arma, pos_x, pos_y);

    if (estado_disparo == MOVER_DERECHA) {
        if (direccion_pato == DIRECCION_DERECHA) {
            rect_dibujado_bala.SetX(rect_dibujado_bala.GetX() + velocidad_bala);
        } else {
            rect_dibujado_bala.SetX(rect_dibujado_bala.GetX() - velocidad_bala);
        }
        mostrar_frame_bala(direccion_pato, it);
    } else {
        reiniciar_bala(pos_x, pos_y);
        mostrar_frame_arma(direccion_pato);
    }
}

void Disparo::reiniciar_bala(int pos_x, int pos_y) {
    rect_dibujado_bala.SetX(pos_x + 5);
    rect_dibujado_bala.SetY(pos_y);
}

void Disparo::cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
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
