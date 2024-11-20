#include "tile_interfaz.h"
#define PIXEL_TILE 16

TileInterfaz::TileInterfaz(SDL2pp::Surface& superficie, std::string path, int x, int y)
    : tile_surface(IMG_Load(path.c_str())), 
    superficie(superficie), 
    rectangulo(x, y, PIXEL_TILE, PIXEL_TILE) {}

TileInterfaz::TileInterfaz(TileInterfaz&& other) noexcept
    : tile_surface(std::move(other.tile_surface)),
    superficie(other.superficie),
    rectangulo(std::move(other.rectangulo)) {}

TileInterfaz& TileInterfaz::operator=(TileInterfaz&& other) noexcept {
    if (this != &other) {  
        tile_surface = std::move(other.tile_surface);  
        rectangulo = std::move(other.rectangulo);  
        
    }
    return *this;
}

void TileInterfaz::dibujar() {
    SDL_BlitScaled(tile_surface.Get(), nullptr, superficie.Get(), &rectangulo);
}

int TileInterfaz::get_pos_x() { return rectangulo.x; }

int TileInterfaz::get_pos_y() { return rectangulo.y; }
