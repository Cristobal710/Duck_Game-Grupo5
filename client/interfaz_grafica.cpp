#include "interfaz_grafica.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../common/common_pato.h"
#include "../common/common_estado_pato.h"
#include "../common/common_constantes.h"
#include <cmath>

#define DURACION_FRAME 1000 / 30 // 30 frames por segundo

InterfazGrafica::InterfazGrafica(Queue<ComandoGrafica>& queue, Queue<EstadoJuego>& cola_estado_juego):
        comandos_cliente(queue),
        estado_juego(cola_estado_juego),
        correr_programa(true),
        window(SDL2pp::Window("SDL2 Image Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              1280, 720, SDL_WINDOW_RESIZABLE)),
        renderer(window, -1, SDL_RENDERER_ACCELERATED), 
        fondo(renderer, "../resources/backgrounds/forest.png"),
        pato(renderer, "../resources/Grey-Duck.png")

{}

void InterfazGrafica::iniciar() {

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL2pp::Surface sprite_pato_gris(IMG_Load("../resources/Grey-Duck.png"));
    //PatoInterfaz pato = PatoInterfaz(renderer, sprite_pato_gris);
    //FondoInterfaz fondo = FondoInterfaz(renderer, "../resources/forest.png");

    SDL2pp::Rect rect_inicio = {1, 8, 32, 32};
    SDL2pp::Rect rect_dibujado = {100, 100, 32, 32};  // posición inicial

    uint8_t estado_pato = BYTE_NULO;
    uint8_t direccion_pato = DIRECCION_DERECHA;
    
    float tiempo_ultimo_frame = SDL_GetTicks();
    int it = 0;

    while (correr_programa) {
        
        manejar_eventos(rect_inicio, rect_dibujado, pato);
        renderer.Clear();
        obtener_estado_juego(rect_dibujado, estado_pato, direccion_pato);
        fondo.dibujar(renderer);
        pato.dibujar(estado_pato, direccion_pato, rect_dibujado.GetX(), rect_dibujado.GetY(), it);
        renderer.Present();
            
        
        //ahora calculamos cuanto tardamos en hacer todo, si nos pasamos, drop & rest.
        Uint32 tiempo_actual = SDL_GetTicks();
        int32_t descansar = DURACION_FRAME - (tiempo_actual - tiempo_ultimo_frame);

        if (descansar < 0){ //entonces nos atrasamos, tenemos que esperar a la siguiente iteracion, drop & rest.
            int32_t behind = -descansar;  
            descansar = DURACION_FRAME - (behind % DURACION_FRAME);
            int32_t lost = behind + descansar;

            tiempo_ultimo_frame += lost;
            it += static_cast<int>(lost / DURACION_FRAME);
            if (lost % DURACION_FRAME != 0 && (lost < 0) != (DURACION_FRAME < 0)) {
                it--;  
            }
        }
        SDL_Delay(descansar);
        tiempo_ultimo_frame += DURACION_FRAME;
        it += 1;
        
    }

    IMG_Quit();
    SDL_Quit();
}

void InterfazGrafica::manejar_eventos(SDL_Rect& rect_inicio, SDL2pp::Rect& rect_dibujado,
                                      PatoInterfaz& pato) {
    SDL_Event evento;
    while (SDL_PollEvent(&evento)) {

        ComandoGrafica comando_cliente;

        if (evento.type == SDL_QUIT) {
            correr_programa = false;

        } else if (evento.type == SDL_KEYDOWN) {
            if (evento.key.keysym.sym == SDLK_ESCAPE) {
                correr_programa = false;
            }
            if (evento.key.keysym.sym == SDLK_d) {
                comando_cliente.tecla = "d";
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
            }
            if (evento.key.keysym.sym == SDLK_a) {
                comando_cliente.tecla = "a";
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
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

void InterfazGrafica::obtener_estado_juego(SDL2pp::Rect& rect_destino, uint8_t& estado_pato, uint8_t& direccion_pato) {
    //deberia ser bloqueante?
    EstadoJuego ultimo_estado; 
    // cambiar if por while hasta quedarme con el ulitmo estado de juego y dibujo el ultimo
    if (estado_juego.try_pop(ultimo_estado)) {
        Pato pato = ultimo_estado.patos.front();
        rect_destino.SetX(pato.get_pos_x());
        rect_destino.SetY(pato.get_pos_y());
        estado_pato = pato.estado.get_estado_movimiento();
        direccion_pato = pato.get_direccion();

    } else {
        estado_pato = false;
    }
}

