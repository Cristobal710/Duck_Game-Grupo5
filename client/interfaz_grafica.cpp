#include "interfaz_grafica.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

InterfazGrafica::InterfazGrafica() : correr_programa(true),
    window(SDL2pp::Window("SDL2 Image Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_RESIZABLE)),
    renderer(window, -1, SDL_RENDERER_ACCELERATED)

{}

void InterfazGrafica::iniciar() {
    
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL2pp::Surface sprite_pato_gris(IMG_Load("../resources/Grey-Duck.png"));
    PatoInterfaz pato = PatoInterfaz(renderer, sprite_pato_gris);
    FondoInterfaz fondo = FondoInterfaz(renderer, "../resources/forest.webp");

    SDL2pp::Rect rect_inicio = {1, 8, 32, 32};
    SDL2pp::Rect rect_dibujado = {100, 100, 32, 32}; // posición inicial

    while (correr_programa) {
        manejar_eventos(rect_inicio, rect_dibujado, pato);
        renderer.Clear();
        fondo.dibujar(renderer);
        pato.dibujar(renderer, rect_inicio, rect_dibujado);
        renderer.Present();
    }
    IMG_Quit();
    SDL_Quit();
}

void InterfazGrafica::manejar_eventos(SDL_Rect& rect_inicio, SDL2pp::Rect& rect_dibujado, PatoInterfaz& pato) {
    SDL_Event evento;
    while (SDL_PollEvent(&evento)) {
        if (evento.type == SDL_QUIT) {
            correr_programa = false;
        }
        else if (evento.type == SDL_KEYDOWN) {
            if (evento.key.keysym.sym == SDLK_ESCAPE) {
                correr_programa = false;
            }
            if (evento.key.keysym.sym == SDLK_d) {
                pato.pato_camina_derecha(renderer, rect_inicio, rect_dibujado);
            }
            if (evento.key.keysym.sym == SDLK_a) {
                pato.pato_camina_izquierda(renderer, rect_inicio, rect_dibujado);
            }
            if (evento.key.keysym.sym == SDLK_SPACE) {
                pato.pato_salta(renderer, rect_inicio, rect_dibujado);
            }
            if (evento.key.keysym.sym == SDLK_DOWN) {
                pato.pato_agachado(renderer, rect_inicio, rect_dibujado);
            }
        }
    }
}

