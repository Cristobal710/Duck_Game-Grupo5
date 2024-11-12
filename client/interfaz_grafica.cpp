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
        pato(renderer, "../resources/Grey-Duck.png", 0 , 0),
        disparo(renderer, "../resources/weapons/Darts.png", "../resources/weapons/Darts.png", 0, 0)

{}

void InterfazGrafica::iniciar() {

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL2pp::Surface sprite_pato_gris(IMG_Load("../resources/Grey-Duck.png"));
    

    std::vector<EntidadInterfaz> entidades;

    SDL2pp::Rect rect_dibujado = {100, 100, 32, 32};  // posición inicial

    float zoom_factor = 2.0f;

    //uint8_t estado_disparo = BYTE_NULO;
    
    //MAPA mapa_a_jugar = ();
    //mapa_a_jugar.procesar();

    // while (jugando_juego){

    // }

    PatoInterfaz pato2(renderer, "../resources/Random/White-Duck.png", 400, 400);
    PatoInterfaz pato3(renderer, "../resources/Random/Yellow-Duck.png", 1200, 700);

    int it = 0;
    while (correr_programa) {
        float tiempo_ultimo_frame = SDL_GetTicks();
        
        renderer.Clear();
        manejar_eventos();
        obtener_estado_juego();
        
        fondo.dibujar(renderer, 1.0f, 2.0f, rect_dibujado.GetX(), rect_dibujado.GetY(), 1200, 700);
        pato.dibujar(it, zoom_factor);
        //disparo.mostrar_disparo(estado_pato_movimiento, direccion_pato, rect_dibujado.GetX(), rect_dibujado.GetY(), it, zoom_factor);
        
        pato2.dibujar(it, 1.0f);
        pato3.dibujar(it, 1.0f);
        renderer.Present();
            
        
        //ahora calculamos cuanto tardamos en hacer todo, si nos pasamos, drop & rest.
        Uint32 tiempo_actual = SDL_GetTicks();
        int32_t descansar = DURACION_FRAME - (tiempo_actual - tiempo_ultimo_frame);

        if (descansar < 0){ //entonces nos atrasamos, tenemos que esperar a la siguiente iteracion, drop & rest.
            int32_t tiempo_atrasado = -descansar;  
            descansar = DURACION_FRAME - (tiempo_atrasado % DURACION_FRAME);
            int32_t tiempo_perdido = tiempo_atrasado + descansar;

            tiempo_ultimo_frame += tiempo_perdido;
            it += static_cast<int>(tiempo_perdido / DURACION_FRAME);
            if (tiempo_perdido % DURACION_FRAME != 0 && (tiempo_perdido < 0) != (DURACION_FRAME < 0)) {
                it--;  
            }
            std::cout << "pierdo un frame" << std::endl;
        }
        SDL_Delay(descansar);
        it += 1;
        tiempo_ultimo_frame = tiempo_actual;  
    }

    IMG_Quit();
    SDL_Quit();
}

void InterfazGrafica::manejar_eventos() {
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
            if (evento.key.keysym.sym == SDLK_w) {
                comando_cliente.tecla = "w";
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
            }
            if (evento.key.keysym.sym == SDLK_s) {
                comando_cliente.tecla = "s";
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
            }
            if (evento.key.keysym.sym == SDLK_SPACE) {
                comando_cliente.tecla = " ";
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
            }
            if (evento.key.keysym.sym == SDLK_f) {
                comando_cliente.tecla = "f";
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
            }
            if (evento.key.keysym.sym == SDLK_g) {
                comando_cliente.tecla = "g";
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
            }
        }
    }
}

void InterfazGrafica::obtener_estado_juego() {
    //deberia ser bloqueante?
    EstadoJuego ultimo_estado; 
    bool hubo_estado_nuevo = false;
    // cambiar if por while hasta quedarme con el ulitmo estado de juego y dibujo el ultimo

    while (estado_juego.try_pop(ultimo_estado)) {
        Pato pato_juego = ultimo_estado.patos.front();
        pato.actualizar_posicion(pato_juego.get_pos_x(), pato_juego.get_pos_y());
        pato.actualizar_estado(pato_juego.estado.get_estado_movimiento(), ESTADO_MOVIMIENTO);
        pato.actualizar_estado(pato_juego.estado.get_estado_salto(), ESTADO_SALTO);
        pato.actualizar_estado(pato_juego.get_direccion(), ESTADO_DIRECCION);
        pato.actualizar_estado(pato_juego.estado.get_estado_agachado(), ESTADO_PISO);
        pato.actualizar_equipamiento(pato_juego.estado.get_estado_movimiento(), ESTADO_ARMA);
        pato.actualizar_equipamiento(pato_juego.estado.get_estado_movimiento(), ESTADO_ARMADURA);
        pato.actualizar_equipamiento(pato_juego.estado.get_estado_movimiento(), ESTADO_CASCO);
       
        hubo_estado_nuevo = true;
    } 
    if (!hubo_estado_nuevo){
        pato.actualizar_estado(BYTE_NULO, ESTADO_MOVIMIENTO);
        pato.actualizar_estado(BYTE_NULO, ESTADO_SALTO);
    }
}

