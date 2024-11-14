#include "interfaz_grafica.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../common/common_pato.h"
#include "../common/common_estado_pato.h"
#include "../common/common_constantes.h"
#include <cmath>
#include "../common/common_bala.h"
#define DURACION_FRAME 1000 / 30 // 30 frames por segundo


InterfazGrafica::InterfazGrafica(Queue<ComandoGrafica>& queue, Queue<EstadoJuego>& cola_estado_juego):
        comandos_cliente(queue),
        estado_juego(cola_estado_juego),
        correr_programa(true),
        window(SDL2pp::Window("SDL2 Image Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              1280, 720, SDL_WINDOW_RESIZABLE)),
        renderer(window, -1, SDL_RENDERER_ACCELERATED), 
        pato(renderer, "../resources/Grey-Duck.png", 0 , 0, 0)
{}

void InterfazGrafica::iniciar() {

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    

    std::vector<EntidadInterfaz> entidades;

    SDL2pp::Rect rect_dibujado = {100, 100, 32, 32};  // posición inicial

    //float zoom_factor = 2.0f;

    
    MapaInterfaz mapa_a_jugar(renderer);
    obtener_estado_juego(mapa_a_jugar);



    int it = 0;
    while (correr_programa) {
        float tiempo_ultimo_frame = SDL_GetTicks();
        
        renderer.Clear();
        manejar_eventos();
        obtener_estado_juego(mapa_a_jugar);
        
        mapa_a_jugar.dibujar(rect_dibujado.GetX(), rect_dibujado.GetY(), 1200, 700, it);
        renderer.Present();
            
        
        //ahora calculamos cuanto tardamos en hacer todo, si nos pasamos, drop & rest.
        drop_rest(tiempo_ultimo_frame, it);
    }

    IMG_Quit();
    SDL_Quit();
}

void InterfazGrafica::drop_rest(float& tiempo_ultimo_frame, int& it) {
    Uint32 tiempo_actual = SDL_GetTicks();
    int32_t descansar = DURACION_FRAME - (tiempo_actual - tiempo_ultimo_frame);

    if (descansar < 0) {  // entonces nos atrasamos, tenemos que esperar a la siguiente iteracion, drop & rest.
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
                        comando_cliente.tecla = DERECHA;
                        comando_cliente.jugador_id = 3;
                        comandos_cliente.push(comando_cliente);
                    }
                    if (evento.key.keysym.sym == SDLK_a) {
                        comando_cliente.tecla = IZQUIERDA;
                        comando_cliente.jugador_id = 3;
                        comandos_cliente.push(comando_cliente);
                    }
                    if (evento.key.keysym.sym == SDLK_w) {
                        comando_cliente.tecla = ARRIBA;
                        comando_cliente.jugador_id = 3;
                        comandos_cliente.push(comando_cliente);
                    }
                    if (evento.key.keysym.sym == SDLK_s) {
                        comando_cliente.tecla = ABAJO;
                        comando_cliente.jugador_id = 3;
                        comandos_cliente.push(comando_cliente);
                    }
                    if (evento.key.keysym.sym == SDLK_SPACE) {
                        comando_cliente.tecla = SALTO;
                        comando_cliente.jugador_id = 3;
                        comandos_cliente.push(comando_cliente);
                    }
                    if (evento.key.keysym.sym == SDLK_f) {
                        comando_cliente.tecla = DISPARO;
                        comando_cliente.jugador_id = 3;
                        comandos_cliente.push(comando_cliente);
                    }
                    if (evento.key.keysym.sym == SDLK_g) {
                        comando_cliente.tecla = AGARRAR_ARMA;
                        comando_cliente.jugador_id = 3;
                        comandos_cliente.push(comando_cliente);
                    }
        } else if (evento.type == SDL_KEYUP) {
            // When the key is released, stop the movement
            if (evento.key.keysym.sym == SDLK_d) {
                comando_cliente.tecla = NO_DERECHA;
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
            }
            if (evento.key.keysym.sym == SDLK_a) {
                comando_cliente.tecla = NO_IZQUIERDA;
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
            }
            if (evento.key.keysym.sym == SDLK_w) {
                comando_cliente.tecla = NO_ARRIBA;
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
            }
            if (evento.key.keysym.sym == SDLK_s) {
                comando_cliente.tecla = NO_ABAJO;
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
            }
            if (evento.key.keysym.sym == SDLK_SPACE) {
                comando_cliente.tecla = NO_SALTO;
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
            }
            if (evento.key.keysym.sym == SDLK_f) {
                comando_cliente.tecla = NO_DISPARO;
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
            }
            if (evento.key.keysym.sym == SDLK_g) {
                comando_cliente.tecla = NO_AGARRAR_ARMA;
                comando_cliente.jugador_id = 3;
                comandos_cliente.push(comando_cliente);
            }
        }
    }
}

void InterfazGrafica::obtener_estado_juego(MapaInterfaz& mapa) {
    
    EstadoJuego ultimo_estado;  
    
    if (!estado_juego.try_pop(ultimo_estado)){
        return;
    }

    Mapa mapa_a_jugar = ultimo_estado.mapa;
    


    if (!mapa.esta_procesado()){
        
        //procesar fondo
        std::string fondo = mapa_a_jugar.getFondo();
        if (!fondo.empty()){
            mapa.set_fondo(fondo);
        }


        //procesar tiles
        std::map<std::string, std::vector<SDL_Point>> tiles = mapa_a_jugar.getTiles();

        for (const auto& textura_punto : tiles) {
            
            std::string path_textura = textura_punto.first;

            std::vector<SDL_Point> puntos = textura_punto.second;


            for (const auto& punto : puntos){
                mapa.agregar_tile(path_textura, punto.x, punto.y);
            }
        }

        // procesar spawns
        std::map<std::string, std::vector<SDL_Point>> spawns = mapa_a_jugar.getSpawns();

        std::cout << spawns.size() << std::endl;

        for (const auto& id_posicion : spawns) {
            
            std::string id_jugador = id_posicion.first;

            std::vector<SDL_Point> posicion = id_posicion.second;

            std::cout << id_jugador << std::endl;
            mapa.agregar_spawn(id_jugador, posicion.front().x, posicion.front().y);
        }

        mapa.procesado();
    }
    
    
    bool hubo_estado_nuevo = false;

    while (estado_juego.try_pop(ultimo_estado)) {
        for (Pato pato_juego: ultimo_estado.patos) {
            if (pato_juego.get_id() != 3){
                break;
            }
            PatoInterfaz& pato_prueba = mapa.get_pato_con_id(pato_juego.get_id());
            //pato = mapa.get_pato_con_id(pato_juego.get_id());
            pato_prueba.actualizar_posicion(pato_juego.get_pos_x(), pato_juego.get_pos_y());
            pato_prueba.actualizar_estado(pato_juego.estado.get_estado_movimiento(), ESTADO_MOVIMIENTO);
            pato_prueba.actualizar_estado(pato_juego.estado.get_estado_salto(), ESTADO_SALTO);
            pato_prueba.actualizar_estado(pato_juego.get_direccion(), ESTADO_DIRECCION);
            pato_prueba.actualizar_estado(pato_juego.estado.get_estado_agachado(), ESTADO_PISO);
            pato_prueba.actualizar_equipamiento(pato_juego.tiene_arma(), ESTADO_ARMA);
            pato_prueba.actualizar_equipamiento(pato_juego.estado.get_estado_disparo(), ESTADO_BALAS);
            pato_prueba.actualizar_equipamiento(pato_juego.get_arma()->get_municion_disponible(), ESTADO_MUNICION);
            //pato.actualizar_equipamiento(pato_juego.estado.get_estado_movimiento(), ESTADO_ARMADURA);
            //pato.actualizar_equipamiento(pato_juego.estado.get_estado_movimiento(), ESTADO_CASCO);
            //pato_prueba.get_arma().set_tipo_arma(pato_juego.get_arma().get_tipo_arma());
        }
        for (Bala balas_juego: ultimo_estado.balas) {
            //pato_prueba.actualizar_posicion_bala(balas_juego.get_pos_x(), balas_juego.get_pos_y());
            std::cout << "pos x bala:" << static_cast<int>(balas_juego.get_pos_x()) << std::endl;
            std::cout << "pos y bala:" << static_cast<int>(balas_juego.get_pos_y()) << std::endl;
        }
        //std::cout << "municion:" << static_cast<int>(pato_juego.get_arma()->get_municion_disponible()) << std::endl;
       

        hubo_estado_nuevo = true;
    } 
    if (!hubo_estado_nuevo){
        for (Pato pato_juego: ultimo_estado.patos) {
            PatoInterfaz& pato_prueba = mapa.get_pato_con_id(pato_juego.get_id());
            pato_prueba.actualizar_estado(BYTE_NULO, ESTADO_MOVIMIENTO);
            pato_prueba.actualizar_estado(BYTE_NULO, ESTADO_SALTO);
            //pato_prueba.actualizar_estado(BYTE_NULO, ESTADO_PISO);
        }
    }
    
}

