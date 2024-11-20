#ifndef FONDO_INTERFAZ_H
#define FONDO_INTERFAZ_H
#define MIN_ZOOM 1.0f
#define MAX_ZOOM 2.4f
#include <SDL2pp/SDL2pp.hh>
#include <string>

class FondoInterfaz {
private:
    //SDL2pp::Renderer& renderer;  
    SDL2pp::Surface& superficie;
    SDL2pp::Surface fondo_surface;
    SDL2pp::Rect rectangulo;
    //SDL2pp::Texture fondo_texture; 

public:
    
    FondoInterfaz(SDL2pp::Surface& superficie, std::string path_fondo);

    FondoInterfaz(FondoInterfaz&& other) noexcept;

    FondoInterfaz& operator=(FondoInterfaz&& other) noexcept;

    FondoInterfaz(const FondoInterfaz& other) = delete;
    FondoInterfaz& operator=(const FondoInterfaz& other) = delete;

    void set_fondo(std::string path_fondo);
    void dibujar();
};

#endif  // FONDO_INTERFAZ_H

