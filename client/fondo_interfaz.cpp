#include "fondo_interfaz.h"
#include <SDL2/SDL_image.h>

FondoInterfaz::FondoInterfaz(SDL2pp::Renderer& renderer, const std::string& fondo_path):
        fondo_texture(renderer, SDL2pp::Surface(IMG_Load(fondo_path.c_str()))) {}


void FondoInterfaz::dibujar(SDL2pp::Renderer& renderer, float zoom_minimo, float zoom_maximo, 
                            int pato1_x, int pato1_y, int pato2_x, int pato2_y) {
    int window_width, window_height;
    SDL_GetRendererOutputSize(renderer.Get(), &window_width, &window_height);

    float distancia = std::sqrt(std::pow(pato2_x - pato1_x, 2) + std::pow(pato2_y - pato1_y, 2));

    float limite_distancia = 900.0f; 

    float zoom_factor;

    if (distancia > limite_distancia) {
       
        zoom_factor = 1.0f;
    } else {
        
        zoom_factor = std::max(zoom_minimo, std::min(zoom_maximo, zoom_maximo - (distancia / 1200.0f)));
    }

    int min_x = std::min(pato1_x, pato2_x);
    int max_x = std::max(pato1_x, pato2_x);
    int min_y = std::min(pato1_y, pato2_y);
    int max_y = std::max(pato1_y, pato2_y);


    int padding = 50; 
    min_x -= padding;
    max_x += padding;
    min_y -= padding;
    max_y += padding;

   
    int background_width = fondo_texture.GetWidth();
    int background_height = fondo_texture.GetHeight();

  
    int visible_width = static_cast<int>(window_width / zoom_factor);
    int visible_height = static_cast<int>(window_height / zoom_factor);

   
    visible_width = std::min(visible_width, background_width);
    visible_height = std::min(visible_height, background_height);

    
    int center_x = (min_x + max_x) / 2;
    int center_y = (min_y + max_y) / 2;

    
    int nuevo_x = center_x - visible_width / 2;
    int nuevo_y = center_y - visible_height / 2;

    nuevo_x = std::max(0, std::min(nuevo_x, background_width - visible_width));
    nuevo_y = std::max(0, std::min(nuevo_y, background_height - visible_height));

    
    SDL2pp::Rect destination_rect(
        -nuevo_x,  
        -nuevo_y,   
        static_cast<int>(window_width * zoom_factor),
        static_cast<int>(window_height * zoom_factor)
    );

    renderer.Copy(fondo_texture, SDL2pp::Optional<SDL2pp::Rect>(), destination_rect);
}



   






