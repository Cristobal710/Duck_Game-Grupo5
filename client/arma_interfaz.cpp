#include "arma_interfaz.h"

ArmaInterfaz::ArmaInterfaz(SDL2pp::Renderer& renderer, const std::string& arma_path, 
                                int pos_x, int pos_y) :
        renderer(renderer),
        arma(),
        rect_inicio_arma(0, 0, PIXEL_ARMA, PIXEL_ARMA), 
        rect_dibujado_arma(pos_x, pos_y, PIXEL_ARMA, PIXEL_ARMA),
        municion_disponible(0)
{
    SDL2pp::Surface sprite_arma(IMG_Load(arma_path.c_str()));
    cargar_frames(renderer, sprite_arma, 0, arma, 1, 0, PIXEL_ARMA, PIXEL_ARMA);
}

void ArmaInterfaz::set_municion(uint8_t municion) {
    municion_disponible = municion;
}

uint8_t ArmaInterfaz::get_municion_disponible() {
    return municion_disponible;
}

void ArmaInterfaz::set_posicion(int pos_x, int pos_y, float& zoom_factor) {
    rect_dibujado_arma.SetX(pos_x);
    rect_dibujado_arma.SetY(pos_y);
    set_zoom_in(zoom_factor, rect_dibujado_arma, pos_x, pos_y);
}

void ArmaInterfaz::dibujar(uint8_t& direccion_pato) {
    if (direccion_pato == DIRECCION_DERECHA) {
        renderer.Copy(arma[0], rect_inicio_arma, rect_dibujado_arma);
    } else {
        SDL_RenderCopyEx(renderer.Get(), arma[0].Get(), &rect_inicio_arma, &rect_dibujado_arma, 0, nullptr, SDL_FLIP_HORIZONTAL);
    }
}

void ArmaInterfaz::cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
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

void ArmaInterfaz::set_zoom_in(float& zoom_factor, SDL2pp::Rect& rect_dibujado, int& pos_x, int& pos_y) {
    int original_width = PIXEL_ARMA;
    int original_height = PIXEL_ARMA;
    rect_dibujado.SetW(static_cast<int>(original_width * zoom_factor));
    rect_dibujado.SetH(static_cast<int>(original_height * zoom_factor));

    rect_dibujado.SetX(pos_x - (rect_dibujado.GetW() - original_width) / 2);
    rect_dibujado.SetY(pos_y - (rect_dibujado.GetH() - original_height) / 2);
}

