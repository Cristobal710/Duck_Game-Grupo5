#include "fondo_interfaz.h"
#include <SDL2/SDL_image.h>

FondoInterfaz::FondoInterfaz(SDL2pp::Renderer& renderer, const std::string& fondo_path)
    : fondo_texture(renderer, SDL2pp::Surface(IMG_Load(fondo_path.c_str())))
{}

void FondoInterfaz::dibujar(SDL2pp::Renderer& renderer) {
    renderer.Copy(fondo_texture, SDL2pp::Optional<SDL2pp::Rect>(), SDL2pp::Optional<SDL2pp::Rect>());
}

