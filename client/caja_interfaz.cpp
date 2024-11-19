#include "caja_interfaz.h"

#define PIXEL_CAJA 16

CajaInterfaz::CajaInterfaz(SDL2pp::Renderer& renderer, uint16_t id, std::string path, int x, int y) 
    : renderer(renderer),
    caja_texture(renderer, SDL2pp::Surface(IMG_Load(path.c_str()))),
    rectangulo(x, y, PIXEL_CAJA, PIXEL_CAJA),
    id(id) {}

void CajaInterfaz::dibujar() {
    renderer.Copy(caja_texture, SDL2pp::NullOpt, rectangulo);
}
