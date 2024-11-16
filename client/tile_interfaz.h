#ifndef TILE_INTERFAZ_H
#define TILE_INTERFAZ_H
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TileInterfaz {
    private:
    SDL2pp::Renderer& renderer;  
    SDL2pp::Texture tile_texture;
    SDL2pp::Rect rectangulo; 

    public:
    TileInterfaz(SDL2pp::Renderer& renderer, std::string path, int x, int y);
   
    TileInterfaz(TileInterfaz&& other) noexcept;

    
    TileInterfaz& operator=(TileInterfaz&& other) noexcept;

    
    TileInterfaz(const TileInterfaz& other) = delete;
    TileInterfaz& operator=(const TileInterfaz& other) = delete;

    void dibujar(float zoom_factor, int pos_x, int pos_y);
    void set_zoom_in(float& zoom_factor, SDL2pp::Rect& source_rect, int& pos_x, int& pos_y);
    int get_pos_x();
    int get_pos_y();
};



#endif
