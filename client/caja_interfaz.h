#ifndef CAJA_INTERFAZ_H
#define CAJA_INTERFAZ_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>

class CajaInterfaz {
private:
    SDL2pp::Surface caja_surface;
    SDL2pp::Surface& superficie;
    SDL2pp::Rect rectangulo;

public:
    CajaInterfaz(SDL2pp::Surface& superficie, std::string path, int x, int y);

    CajaInterfaz(CajaInterfaz&& other) noexcept;
    CajaInterfaz& operator=(CajaInterfaz&& other) noexcept;
    
    CajaInterfaz(const CajaInterfaz& other) = delete;
    CajaInterfaz& operator=(const CajaInterfaz& other) = delete;

    void dibujar();
    
};

#endif
