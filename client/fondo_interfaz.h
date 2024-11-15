#ifndef FONDO_INTERFAZ_H
#define FONDO_INTERFAZ_H
#define MIN_ZOOM 1.0f
#define MAX_ZOOM 2.4f
#include <SDL2pp/SDL2pp.hh>
#include <string>

class FondoInterfaz {
private:
    SDL2pp::Renderer& renderer;  
    SDL2pp::Texture fondo_texture; 

public:
    
    FondoInterfaz(SDL2pp::Renderer& renderer, const std::string& fondo_path);

   
    FondoInterfaz(FondoInterfaz&& other) noexcept;

    
    FondoInterfaz& operator=(FondoInterfaz&& other) noexcept;


    void dibujar(float& zoom_factor, 
                 int duck1_x, int duck1_y);
};

#endif  // FONDO_INTERFAZ_H

