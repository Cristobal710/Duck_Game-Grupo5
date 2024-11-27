#include "caja_interfaz.h"

#define PIXEL_CAJA 16

CajaInterfaz::CajaInterfaz(SDL2pp::Surface& superficie, std::string path, int x, int y) 
    : caja_surface(IMG_Load(path.c_str())),
    superficie(superficie),
    rectangulo(x, y, PIXEL_CAJA, PIXEL_CAJA), recogida(false) {}

CajaInterfaz::CajaInterfaz(CajaInterfaz&& other) noexcept
    : caja_surface(std::move(other.caja_surface)),
    superficie(other.superficie),
    rectangulo(std::move(other.rectangulo)) {}

CajaInterfaz& CajaInterfaz::operator=(CajaInterfaz&& other) noexcept {
    if (this != &other) {
        caja_surface = std::move(other.caja_surface);
        rectangulo = std::move(other.rectangulo);
    }
    return *this;
}

void CajaInterfaz::dibujar() {
    if (!recogida) {
        SDL_BlitScaled(caja_surface.Get(), nullptr, superficie.Get(), &rectangulo);
    }
}

bool CajaInterfaz::misma_caja(int x, int y) {  
    if (x == rectangulo.x && y == rectangulo.y){
        return true;
    }
    return false;
}

void CajaInterfaz::no_dibujar() {
    recogida = true;
}
