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

    void dibujar();
};



#endif
