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


void FondoInterfaz::dibujar(float& zoom_factor, int pato1_x, int pato1_y) {
    int window_width, window_height;
    
    SDL_GetRendererOutputSize(renderer.Get(), &window_width, &window_height);

    int background_width = fondo_texture.GetWidth();
    int background_height = fondo_texture.GetHeight();

    int zoomed_width = static_cast<int>(background_width / zoom_factor); 
    int zoomed_height = static_cast<int>(background_height / zoom_factor);


    int camera_x = pato1_x - window_width / 2 / zoom_factor;
    int camera_y = pato1_y - window_height / 2 / zoom_factor; //sacar el zoom factor de aca puede
                                                              //ayudar a calcular mejor

    camera_x = std::max(0, std::min(camera_x, background_width - zoomed_width));
    camera_y = std::max(0, std::min(camera_y, background_height - zoomed_height));

   
    SDL2pp::Rect source_rect(
        camera_x,            
        camera_y,
        zoomed_width,        
        zoomed_height        
    );

    SDL2pp::Rect destination_rect(0, 0, window_width, window_height);

    renderer.Copy(fondo_texture, source_rect, destination_rect);
}



   






