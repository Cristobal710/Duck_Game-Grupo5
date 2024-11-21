#include "fondo_interfaz.h"
#include <SDL2/SDL_image.h>
#include <cmath>  
#include <algorithm>  


FondoInterfaz::FondoInterfaz(SDL2pp::Surface& superficie, std::string path_fondo)
    : superficie(superficie),
    fondo_surface(IMG_Load(path_fondo.c_str())),
    rectangulo(0, 0, 1280, 720) {}

FondoInterfaz::FondoInterfaz(FondoInterfaz&& other) noexcept
    : superficie(other.superficie),
    fondo_surface(std::move(other.fondo_surface)),
    rectangulo(std::move(other.rectangulo)) {}

FondoInterfaz& FondoInterfaz::operator=(FondoInterfaz&& other) noexcept {
    if (this != &other) {
        fondo_surface = std::move(other.fondo_surface);
        rectangulo = std::move(other.rectangulo);
    }
    return *this;
}

void FondoInterfaz::set_fondo(std::string path_fondo) {
    try {
        // Load the image using IMG_Load (this returns a raw SDL_Surface*)
        SDL_Surface* raw_surface = IMG_Load(path_fondo.c_str());

        // Now wrap the raw SDL_Surface* in a SDL2pp::Surface
        SDL2pp::Surface nueva_superficie(raw_surface);

        // Assign the new surface to fondo_surface
        fondo_surface = std::move(nueva_superficie);
    } catch (const SDL2pp::Exception& e) {
        std::cerr << "Error al cargar el fondo: " << e.what() << " (" << e.GetSDLError() << ")" << std::endl;
        throw;
    }
}

void FondoInterfaz::dibujar(){
    SDL_BlitScaled(fondo_surface.Get(), nullptr, superficie.Get(), &rectangulo);
}


/*void FondoInterfaz::dibujar(float& zoom_factor, int pato1_x, int pato1_y) {
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
}*/



   






