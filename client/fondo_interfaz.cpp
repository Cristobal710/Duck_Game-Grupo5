#include "fondo_interfaz.h"
#include <SDL2/SDL_image.h>
#include <cmath>  
#include <algorithm>  


FondoInterfaz::FondoInterfaz(SDL2pp::Renderer& renderer, const std::string& fondo_path)
    : renderer(renderer),
    fondo_texture(renderer, SDL2pp::Surface(IMG_Load(fondo_path.c_str()))) {
}


FondoInterfaz::FondoInterfaz(FondoInterfaz&& other) noexcept
    : renderer(other.renderer), fondo_texture(std::move(other.fondo_texture)) {
   
}


FondoInterfaz& FondoInterfaz::operator=(FondoInterfaz&& other) noexcept {
    if (this != &other) {  
        fondo_texture = std::move(other.fondo_texture);  
        
    }
    return *this;
}


void FondoInterfaz::dibujar(float& zoom_factor, 
                            int pato1_x, int pato1_y) {
    int window_width, window_height;
    
    zoom_factor = zoom_factor;
    SDL_GetRendererOutputSize(renderer.Get(), &window_width, &window_height);

    pato1_x = std::max(0, pato1_x);
    pato1_y = std::max(0, pato1_y);

    pato1_x = std::min(pato1_x, window_width);
    pato1_y = std::min(pato1_y, window_height);



    SDL2pp::Rect destination_rect(
        -pato1_x,  
        -pato1_y,   
        window_width,
        window_height
    );

    renderer.Copy(fondo_texture, SDL2pp::Optional<SDL2pp::Rect>(), destination_rect);
}



   






