#ifndef FONDO_INTERFAZ_H
#define FONDO_INTERFAZ_H

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


    void dibujar(float min_zoom, float max_zoom, 
                 int duck1_x, int duck1_y, int duck2_x, int duck2_y);
};

#endif  // FONDO_INTERFAZ_H

