#include "tile_interfaz.h"
#define PIXEL_TILE 32

TileInterfaz::TileInterfaz(SDL2pp::Renderer& renderer, std::string path, int x, int y):
renderer(renderer), tile_texture(renderer, SDL2pp::Surface(IMG_Load(path.c_str()))),
rectangulo(x * 32, y * 32, PIXEL_TILE, PIXEL_TILE)
{}



TileInterfaz::TileInterfaz(TileInterfaz&& other) noexcept
    : renderer(other.renderer), tile_texture(std::move(other.tile_texture)),
      rectangulo(std::move(other.rectangulo)) {
  
}


TileInterfaz& TileInterfaz::operator=(TileInterfaz&& other) noexcept {
    if (this != &other) {  
        tile_texture = std::move(other.tile_texture);  
        rectangulo = std::move(other.rectangulo);  
        
    }
    return *this;
}

void TileInterfaz::dibujar() {
    renderer.Copy(tile_texture, SDL2pp::Optional<SDL2pp::Rect>(),
                      rectangulo);
}
