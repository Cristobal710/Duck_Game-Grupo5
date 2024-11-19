#ifndef CAJA_INTERFAZ_H
#define CAJA_INTERFAZ_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>

class CajaInterfaz {
private:
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture caja_texture;
    SDL2pp::Rect rectangulo;
    uint16_t id;

public:
    CajaInterfaz(SDL2pp::Renderer& renderer, uint16_t id, std::string path, int x, int y);

    void dibujar();
    
};

#endif
