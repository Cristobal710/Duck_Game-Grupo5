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
        
        SDL_Surface* superficie_path = IMG_Load(path_fondo.c_str());

        
        SDL2pp::Surface nueva_superficie(superficie_path);

        fondo_surface = std::move(nueva_superficie);
    } catch (const SDL2pp::Exception& e) {
        std::cerr << "Error al cargar el fondo: " << e.what() << " (" << e.GetSDLError() << ")" << std::endl;
        throw;
    }
}

void FondoInterfaz::dibujar(){
    SDL_BlitScaled(fondo_surface.Get(), nullptr, superficie.Get(), &rectangulo);
}



   






