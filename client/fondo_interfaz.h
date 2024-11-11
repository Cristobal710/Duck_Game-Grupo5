#ifndef FONDO_INTERFAZ_H
#define FONDO_INTERFAZ_H

#include <SDL2pp/SDL2pp.hh>

class FondoInterfaz {
private:
    SDL2pp::Texture fondo_texture;

public:
    FondoInterfaz(SDL2pp::Renderer& renderer, const std::string& fondo_path);
    void dibujar(SDL2pp::Renderer& renderer, float zoom_factor);
};

#endif  // FONDO_INTERFAZ_H
