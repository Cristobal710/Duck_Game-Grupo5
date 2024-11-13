#include "bala_interfaz.h"

#define PIXEL_BALA_X 36
#define PIXEL_BALA_Y 20

BalaInterfaz::BalaInterfaz(SDL2pp::Renderer& renderer, const std::string& bala_path, 
                                int pos_x, int pos_y) :
        bala(), 
        rect_inicio_bala(0, 0, PIXEL_BALA_X, PIXEL_BALA_Y),
        rect_dibujado_bala(pos_x, pos_y, PIXEL_BALA_X, PIXEL_BALA_Y),
        renderer(renderer) 
{
    SDL2pp::Surface sprite_bala(IMG_Load(bala_path.c_str()));
    cargar_frames(renderer, sprite_bala, 22, bala, 3, 83, PIXEL_BALA_X, PIXEL_BALA_Y);
}

void BalaInterfaz::set_posicion_bala(uint16_t pos_x_final, uint16_t pos_y_final) {
    rect_dibujado_bala.SetX(pos_x_final);
    rect_dibujado_bala.SetY(pos_y_final); 
}

void BalaInterfaz::mostrar_frame_bala(uint8_t& direccion_pato) {
    if(direccion_pato == DIRECCION_DERECHA) {
        renderer.Copy(bala[0], rect_inicio_bala, rect_dibujado_bala);
    } else {
        SDL_RenderCopyEx(renderer.Get(), bala[0].Get(), &rect_inicio_bala, &rect_dibujado_bala, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);
    }
}

void BalaInterfaz::cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
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