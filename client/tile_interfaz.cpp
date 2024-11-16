#include "tile_interfaz.h"
#define PIXEL_TILE 16


// void TileInterfaz::set_zoom_in(float& zoom_factor, int& pos_x, int& pos_y) {
    
    

//     int background_width = tile_texture.GetWidth();
//     int background_height = tile_texture.GetHeight();

//     int zoomed_width = static_cast<int>(background_width / zoom_factor); 
//     int zoomed_height = static_cast<int>(background_height / zoom_factor);


//     int camera_x = rectangulo.x - background_width / 2 / zoom_factor;
//     int camera_y = rectangulo.y - background_height / 2 / zoom_factor; //sacar el zoom factor de aca puede
//                                                               //ayudar a calcular mejor

//     camera_x = std::max(0, std::min(camera_x, background_width - zoomed_width));
//     camera_y = std::max(0, std::min(camera_y, background_height - zoomed_height));

    
   
//     pos_x = rectangulo.x - (rectangulo.w - background_width) ;
//     pos_y = rectangulo.y - (rectangulo.h - background_height) ;
// }
// (300, 316) --> (316, 316)    (300, 316) --> (332, 316)
// (300, 316) --> (332, 316)    (316, 316) --> (332, 316)

TileInterfaz::TileInterfaz(SDL2pp::Renderer& renderer, std::string path, int x, int y):
renderer(renderer), tile_texture(renderer, SDL2pp::Surface(IMG_Load(path.c_str()))),
rectangulo(x, y, PIXEL_TILE, PIXEL_TILE)
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

void TileInterfaz::dibujar(float zoom_factor, int pos_x, int pos_y) {

    SDL2pp::Rect rectangulo_a_dibujar(pos_x, pos_y, rectangulo.w * zoom_factor, rectangulo.h * zoom_factor);
    renderer.Copy(tile_texture, SDL2pp::Optional<SDL2pp::Rect>(),
                      rectangulo_a_dibujar);
}

int TileInterfaz::get_pos_x() { return rectangulo.x; }

int TileInterfaz::get_pos_y() { return rectangulo.y; }
