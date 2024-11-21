#ifndef PROCESADOR_SPRITES_H
#define PROCESADOR_SPRITES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

#define PIXEL_PATO 32

class ProcesadorSprites {

public:
    void cargar_frames(SDL2pp::Surface& sprite_sheet, int num_frames, 
        std::vector<SDL2pp::Surface>& texturas, int offset_y, int offset_x, int pixeles_x, int pixeles_y) {
    
    for (int i = 0; i < num_frames; ++i) {
        SDL_Rect rect_inicial = {i * pixeles_x + offset_x, offset_y, pixeles_x, pixeles_y};
        
        SDL2pp::Surface sprite_surface(SDL_CreateRGBSurface(0, pixeles_x, pixeles_y, 32, 0, 0, 0, 0));
        SDL_BlitSurface(sprite_sheet.Get(), &rect_inicial, sprite_surface.Get(), nullptr);

        Uint32 color_key = SDL_MapRGB(sprite_surface.Get()->format, 0, 0, 0);
        SDL_SetColorKey(sprite_surface.Get(), SDL_TRUE, color_key);

        texturas.push_back(std::move(sprite_surface));
    }
}

bool es_gris(SDL_Color pixel) {
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

            if (es_gris(original_color)) {
                uint32_t new_pixel = SDL_MapRGBA(format, color.r, color.g, color.b, original_color.a);
                *pixel_addr = new_pixel;
            }
        }
    }

    SDL_UnlockSurface(sprite_sheet.Get());
}

void flip_horizontal(SDL2pp::Surface& sprite_sheet) {
    int width = sprite_sheet.GetWidth();
    int height = sprite_sheet.GetHeight();

    Uint32* pixels = static_cast<Uint32*>(sprite_sheet.Get()->pixels);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width / 2; ++x) {
            std::swap(pixels[y * width + x], pixels[y * width + (width - x - 1)]);
        }
    }

}

void rotacion_90_grados(SDL2pp::Surface& sprite_sheet) {
    SDL_Surface* sdl_surface = sprite_sheet.Get();

    int width = sprite_sheet.GetWidth();
    int height = sprite_sheet.GetHeight();

    Uint32* rotated_pixels = new Uint32[width * height];

    Uint32* pixels = static_cast<Uint32*>(sdl_surface->pixels);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            rotated_pixels[(width - x - 1) * height + y] = pixels[y * width + x];
        }
    }

    std::copy(rotated_pixels, rotated_pixels + (width * height), pixels);

    delete[] rotated_pixels;

    std::swap(sdl_surface->w, sdl_surface->h);

}

};

#endif
