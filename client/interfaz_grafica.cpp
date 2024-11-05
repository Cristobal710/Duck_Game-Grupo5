#include "interfaz_grafica.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../common/common_pato.h"

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

    bool estado_pato = false;
    Uint32 tiempo_ultimo_frame = SDL_GetTicks();

    while (correr_programa) {
        Uint32 tiempo_actual = SDL_GetTicks();
        Uint32 tiempo_transcurrido = tiempo_actual - tiempo_ultimo_frame;

        if (tiempo_transcurrido >= DURACION_FRAME) {
            manejar_eventos(rect_inicio, rect_dibujado, pato);
            renderer.Clear();
            obtener_estado_juego(rect_dibujado, estado_pato);

            std::string movimiento_pato;
            if (estado_pato) {
                movimiento_pato = "d";
            }

            fondo.dibujar(renderer);
            pato.dibujar(movimiento_pato, rect_dibujado.GetX(), rect_dibujado.GetY());

            renderer.Present();
            
            tiempo_ultimo_frame = tiempo_actual; //resetear el tiempo del ultimo frame al actual
        } else {
            SDL_Delay(DURACION_FRAME - tiempo_transcurrido); //"rest" para evitar uso excesivo de CPU
        }
    }

    IMG_Quit();
    //SDL_DestroyRenderer(renderer);
    //SDL_DestroyWindow(window)
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

void InterfazGrafica::obtener_estado_juego(SDL2pp::Rect& rect_destino, bool& estado_pato) {
    //deberia ser bloqueante?
    EstadoJuego ultimo_estado; 
    if (estado_juego.try_pop(ultimo_estado)) {
        Pato pato = ultimo_estado.patos.front();
        rect_destino.SetX(pato.get_pos_x());
        rect_destino.SetY(pato.get_pos_y());
        estado_pato = pato.se_mueve_derecha;

    } else {
        estado_pato = false;
    }
}

