#include "armadura_interfaz.h"

#define PIXEL_ARMADURA 16

ArmaduraInterfaz::ArmaduraInterfaz(SDL2pp::Renderer& renderer, int pos_x, int pos_y) :
        renderer(renderer),
        armadura(),
        rect_inicio_armadura(0, 0, PIXEL_ARMADURA, PIXEL_ARMADURA),
        rect_dibujado_armadura(pos_x, (pos_y+13), PIXEL_ARMADURA, PIXEL_ARMADURA)
{
    SDL2pp::Surface sprite_armadura(IMG_Load("../resources/armors/chestPlatePickup.png"));
    cargar_frames(renderer, sprite_armadura, 0, armadura, 1, 0, PIXEL_ARMADURA, PIXEL_ARMADURA);
}

void ArmaduraInterfaz::cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
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

void ArmaduraInterfaz::dibujar(uint8_t& direccion_pato, float& zoom_factor) {
    set_zoom_in(zoom_factor, rect_dibujado_armadura, rect_dibujado_armadura.x, rect_dibujado_armadura.y);
    
    if (direccion_pato == DIRECCION_DERECHA) {
        renderer.Copy(armadura[0], rect_inicio_armadura, rect_dibujado_armadura);
    } else {
        SDL_RenderCopyEx(renderer.Get(), armadura[0].Get(), &rect_inicio_armadura, &rect_dibujado_armadura, 0, nullptr, SDL_FLIP_HORIZONTAL);
    }
}

void ArmaduraInterfaz::set_zoom_in(float& zoom_factor, SDL2pp::Rect& rect_dibujado, int& pos_x,
                                   int& pos_y) {
    int original_width = PIXEL_ARMADURA;
    int original_height = PIXEL_ARMADURA;
    rect_dibujado.SetW(static_cast<int>(original_width * zoom_factor));
    rect_dibujado.SetH(static_cast<int>(original_height * zoom_factor));

    rect_dibujado.SetX(pos_x - (rect_dibujado.GetW() - original_width) / 2);
    rect_dibujado.SetY(pos_y - (rect_dibujado.GetH() - original_height) / 2);
}

