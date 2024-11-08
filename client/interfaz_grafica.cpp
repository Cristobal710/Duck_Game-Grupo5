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
        pato(renderer, "../resources/Grey-Duck.png"),
        disparo(renderer, "../resources/weapons/Darts.png", "../resources/weapons/Darts.png", 0, 0)

{}

void InterfazGrafica::iniciar() {

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL2pp::Surface sprite_pato_gris(IMG_Load("../resources/Grey-Duck.png"));
    //PatoInterfaz pato = PatoInterfaz(renderer, sprite_pato_gris);
    //FondoInterfaz fondo = FondoInterfaz(renderer, "../resources/forest.png");

    //SDL2pp::Rect rect_inicio = {1, 8, 32, 32};
    SDL2pp::Rect rect_dibujado = {100, 100, 32, 32};  // posición inicial

    uint8_t estado_pato_movimiento = BYTE_NULO;
    uint8_t se_tira_al_piso = BYTE_NULO;
    uint8_t estado_pato_salto = BYTE_NULO;
    uint8_t direccion_pato = DIRECCION_DERECHA;
    uint8_t estado_disparo = BYTE_NULO;
    
    float tiempo_ultimo_frame = SDL_GetTicks();
    int it = 0;


    //MAPA mapa_a_jugar = ();
    //mapa_a_jugar.procesar();

    // while (jugando_juego){

    // }

    while (correr_programa) {
        
        manejar_eventos();
        renderer.Clear();
        obtener_estado_juego(rect_dibujado, estado_pato_movimiento, se_tira_al_piso, estado_pato_salto, direccion_pato, estado_disparo);
        fondo.dibujar(renderer);
        pato.dibujar(estado_pato_movimiento, estado_pato_salto, direccion_pato, se_tira_al_piso, rect_dibujado.GetX(), rect_dibujado.GetY(), it);
        disparo.mostrar_disparo(estado_pato_movimiento, direccion_pato, rect_dibujado.GetX(), rect_dibujado.GetY(), it);
        //if(estado_disparo == TIENE_ARMA){
        //    disparo.mostrar_disparo(estado_disparo, rect_dibujado.GetX(), rect_dibujado.GetY(), it);
        //}
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
        tiempo_ultimo_frame += DURACION_FRAME;
        it += 1;
        
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
            if (evento.key.keysym.sym == SDL_MOUSEBUTTONDOWN) {
                if (evento.button.button == SDL_BUTTON_LEFT) {
                    comando_cliente.tecla = "click_izq";
                    comando_cliente.jugador_id = 3;
                    comandos_cliente.push(comando_cliente);
                }
            }
        }
    }
}

void InterfazGrafica::obtener_estado_juego(SDL2pp::Rect& rect_destino, uint8_t& estado_pato_movimiento, uint8_t& se_tira_al_piso, uint8_t& estado_pato_salto, uint8_t& direccion_pato, uint8_t& estado_disparo) {
    //deberia ser bloqueante?
    EstadoJuego ultimo_estado; 
    bool hubo_estado_nuevo = false;
    // cambiar if por while hasta quedarme con el ulitmo estado de juego y dibujo el ultimo
    while (estado_juego.try_pop(ultimo_estado)) {
        Pato pato = ultimo_estado.patos.front();
        rect_destino.SetX(pato.get_pos_x());
        rect_destino.SetY(pato.get_pos_y());
        estado_pato_movimiento = pato.estado.get_estado_movimiento();
        se_tira_al_piso = pato.estado.get_estado_agachado();
        estado_pato_salto = pato.estado.get_estado_salto();
        // std::cout <<  "Esta agachado: " << static_cast<int>(se_tira_al_piso) << std::endl;
        // std::cout << "Estado pato: " << static_cast<int>(estado_pato_movimiento) << std::endl;
        // std::cout << "Estado salto: " << static_cast<int>(estado_pato_salto) << std::endl;
        direccion_pato = pato.get_direccion();
        //estado_disparo = pato.estado.get_estado_disparo();
        estado_disparo = BYTE_NULO;
        hubo_estado_nuevo = true;
    } 
    if (!hubo_estado_nuevo){
        estado_pato_movimiento = false;
    }
}

