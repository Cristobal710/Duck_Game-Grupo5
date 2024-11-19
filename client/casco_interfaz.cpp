#include "casco_interfaz.h"

#define PIXEL_CASCO 16

CascoInterfaz::CascoInterfaz(SDL2pp::Renderer& renderer, int pos_x, int pos_y)
    : renderer(renderer),
    casco_texture(),
    rect_inicio_casco(0, 0, PIXEL_CASCO, PIXEL_CASCO),
    rect_dibujado_casco(pos_x, (pos_y-20), PIXEL_CASCO, PIXEL_CASCO)
{
    SDL2pp::Surface sprite_casco(IMG_Load("../resources/armors/knightHelmet.png"));
    cargar_frames(renderer, sprite_casco, 0, casco_texture, 1, 0, PIXEL_CASCO, PIXEL_CASCO);
}

void CascoInterfaz::cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
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

void CascoInterfaz::set_zoom_in(float& zoom_factor, SDL2pp::Rect& rect_dibujado, int& pos_x,
                                int& pos_y) {
    int original_width = PIXEL_CASCO;
    int original_height = PIXEL_CASCO;
    rect_dibujado.SetW(static_cast<int>(original_width * zoom_factor));
    rect_dibujado.SetH(static_cast<int>(original_height * zoom_factor));

    rect_dibujado.SetX(pos_x - (rect_dibujado.GetW() - original_width) / 2);
    rect_dibujado.SetY(pos_y - (rect_dibujado.GetH() - original_height) / 2);
}

void CascoInterfaz::dibujar(uint8_t& direccion_pato, float& zoom_factor) {
    set_zoom_in(zoom_factor, rect_dibujado_casco, rect_dibujado_casco.x, rect_dibujado_casco.y);
    
    if (direccion_pato == DIRECCION_DERECHA) {
        renderer.Copy(casco_texture[0], rect_inicio_casco, rect_dibujado_casco);
    } else {
        SDL_RenderCopyEx(renderer.Get(), casco_texture[0].Get(), &rect_inicio_casco, &rect_dibujado_casco, 0, nullptr, SDL_FLIP_HORIZONTAL);
    }
}
