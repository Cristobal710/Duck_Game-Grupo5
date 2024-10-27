#ifndef INTERFAZ_GRAFICA_H
#define INTERFAZ_GRAFICA_H

#include <exception>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

#include "fondo_interfaz.h"
#include "pato_interfaz.h"

class InterfazGrafica {
private:
    bool correr_programa;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    FondoInterfaz fondo;
    PatoInterfaz pato;

    void manejar_eventos(SDL_Rect& rect_inicio, SDL2pp::Rect& rect_dibujado, PatoInterfaz& pato);

public:
    InterfazGrafica();
    void iniciar();
};

#endif  // INTERFAZ_GRAFICA_H
