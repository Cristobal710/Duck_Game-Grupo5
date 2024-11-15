#include "tile_interfaz.h"
#define PIXEL_TILE 32


void set_zoom_in(float& zoom_factor, SDL2pp::Rect& rect_dibujado, int& pos_x, int& pos_y) {
    int original_width = PIXEL_TILE;
    int original_height = PIXEL_TILE;
    rect_dibujado.SetW(static_cast<int>(original_width * zoom_factor));
    rect_dibujado.SetH(static_cast<int>(original_height * zoom_factor));

    rect_dibujado.SetX(pos_x - (rect_dibujado.GetW() - original_width) / 2);
    rect_dibujado.SetY(pos_y - (rect_dibujado.GetH() - original_height) / 2);
}


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

void TileInterfaz::dibujar(float zoom_factor) {

    int pos_x = rectangulo.GetX();
    int pos_y = rectangulo.GetY();
    
    if (zoom_factor <= 1.0f){
         renderer.Copy(tile_texture, SDL2pp::Optional<SDL2pp::Rect>(),
                      rectangulo);
        return;
    }
    
    set_zoom_in(zoom_factor, rectangulo, pos_x , pos_y);
    renderer.Copy(tile_texture, SDL2pp::Optional<SDL2pp::Rect>(),
                      rectangulo);
   
}

