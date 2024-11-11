#include "fondo_interfaz.h"
#include <SDL2/SDL_image.h>

FondoInterfaz::FondoInterfaz(SDL2pp::Renderer& renderer, const std::string& fondo_path):
        fondo_texture(renderer, SDL2pp::Surface(IMG_Load(fondo_path.c_str()))) {}

void FondoInterfaz::dibujar(SDL2pp::Renderer& renderer, float zoom_factor) {
    int window_width, window_height;
    SDL_GetRendererOutputSize(renderer.Get(), &window_width, &window_height);

    // Scale the background size based on the zoom factor
    SDL2pp::Rect destination_rect(
        0, 0,
        static_cast<int>(window_width * zoom_factor),
        static_cast<int>(window_height * zoom_factor)
    );

    // Center the background if it's zoomed in
    destination_rect.x = (window_width - destination_rect.w) / 2;
    destination_rect.y = (window_height - destination_rect.h) / 2;

    renderer.Copy(fondo_texture, SDL2pp::Optional<SDL2pp::Rect>(), destination_rect);
}



