#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

#define PIXEL_PATO 32

class Movimiento {

public:
    void cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
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

void set_zoom_in(float& zoom_factor, SDL2pp::Rect& rect_dibujado, int& pos_x, int& pos_y) {
    int original_width = PIXEL_PATO;
    int original_height = PIXEL_PATO;
    rect_dibujado.SetW(static_cast<int>(original_width * zoom_factor));
    rect_dibujado.SetH(static_cast<int>(original_height * zoom_factor));
    pos_x = pos_x;
    pos_y = pos_y;
    rect_dibujado.SetX(pos_x - (rect_dibujado.GetW() - original_width) / 2);
    rect_dibujado.SetY(pos_y - (rect_dibujado.GetH() - original_height) / 2);
}

bool is_grey(SDL_Color pixel) {
    const uint8_t tolerance = 30;
    return (abs(pixel.r - pixel.g) < tolerance && abs(pixel.g - pixel.b) < tolerance);
}

void aplicar_color(SDL2pp::Surface& sprite_sheet, SDL_Color color) {
    SDL_LockSurface(sprite_sheet.Get());
    
    uint8_t* pixels = static_cast<uint8_t*>(sprite_sheet.Get()->pixels);
    int pitch = sprite_sheet.Get()->pitch;
    SDL_PixelFormat* format = sprite_sheet.Get()->format;

    for (int y = 0; y < sprite_sheet.Get()->h; ++y) {
        for (int x = 0; x < sprite_sheet.Get()->w; ++x) {
            uint32_t* pixel_addr = reinterpret_cast<uint32_t*>(pixels + y * pitch + x * 4);
            uint32_t pixel = *pixel_addr;

            SDL_Color original_color;
            SDL_GetRGBA(pixel, format, &original_color.r, &original_color.g, &original_color.b, &original_color.a);

            if (is_grey(original_color)) {
                uint32_t new_pixel = SDL_MapRGBA(format, color.r, color.g, color.b, original_color.a);
                *pixel_addr = new_pixel;
            }
        }
    }

    SDL_UnlockSurface(sprite_sheet.Get());
}


};

#endif // MOVIMIENTO_H