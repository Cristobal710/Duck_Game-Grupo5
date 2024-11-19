#include "interfaz_grafica.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../common/common_pato.h"
#include "../common/common_estado_pato.h"
#include "../common/common_constantes.h"
#include <cmath>
#include "../common/common_bala.h"
#include "lobby.h"
#define DURACION_FRAME 1000 / 30 // 30 frames por segundo


InterfazGrafica::InterfazGrafica(Queue<ComandoGrafica>& queue, Queue<EstadoJuego>& cola_estado_juego):
        comandos_cliente(queue),
        estado_juego(cola_estado_juego),
        correr_programa(true),
        window(SDL2pp::Window("SDL2 Image Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              1280, 720, SDL_WINDOW_RESIZABLE)),
        renderer(window, -1, SDL_RENDERER_ACCELERATED)
{}

void InterfazGrafica::iniciar_audio(std::string audio_path){
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_QuerySpec(nullptr, nullptr, nullptr);;
    Mix_Music* music = Mix_LoadMUS(audio_path.c_str());
    Mix_PlayMusic(music, -1);
    //int sdl_volume = static_cast<int>((5 / 10.0) * 128);
    Mix_VolumeMusic(0);
}

void InterfazGrafica::iniciar() {

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    // Create lobby instance
    Lobby lobby(renderer.Get());
    while (!lobby.empezo()) {
        lobby.dibujar();
        lobby.manejar_eventos();
    }

    // aca hay q mandar cuantos jugadores selecciono y si creo una partida nueva
    // o se unio a una existente al servidor
    //por ahora:
    int cant_jugadores = lobby.cantidad_jugadores();
    while(cant_jugadores != 1){
        //loop
    }
    
    std::string audio_fondo_path = "../resources/sounds/background_music.mp3";
    iniciar_audio(audio_fondo_path);
    MapaInterfaz mapa_a_jugar(renderer);
    obtener_estado_juego(mapa_a_jugar);
    
    std::set<SDL_Keycode> keysHeld;
    int it = 0;
    while (correr_programa) {
        float tiempo_ultimo_frame = SDL_GetTicks();
        
        renderer.Clear();
        manejar_eventos(keysHeld);
        obtener_estado_juego(mapa_a_jugar);
        
        mapa_a_jugar.dibujar(it);
        renderer.Present();
            
        //ahora calculamos cuanto tardamos en hacer todo, si nos pasamos, drop & rest.
        drop_rest(tiempo_ultimo_frame, it);

    }

    //Mix_FreeMusic(music);
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
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

void InterfazGrafica::manejar_eventos(std::set<SDL_Keycode>& keysHeld) {
    SDL_Event evento;
    
    while (SDL_PollEvent(&evento)) {
        ComandoGrafica comando_cliente;

        if (evento.type == SDL_QUIT) {
            correr_programa = false;

        } else if (evento.type == SDL_KEYDOWN) {
            if(keysHeld.find(evento.key.keysym.sym) == keysHeld.end()) {
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
            }
            keysHeld.insert(evento.key.keysym.sym);
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
            keysHeld.erase(evento.key.keysym.sym);
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
        for (auto& pato : ultimo_estado.patos) {
            int pos_x = static_cast<int>(pato.get_pos_x());
            int pos_y = static_cast<int>(pato.get_pos_y());
            mapa.agregar_spawn(pato.get_id(), pos_x, pos_y);
        }
        mapa.agregar_spawn(8, 736, 352);

        // procesar cajas 
        std::map<std::string, std::vector<SDL_Point>> cajas = mapa_a_jugar.getCajas();

        for (const auto& caja : cajas) {
            std::string path = caja.first;
            std::vector<SDL_Point> puntos = caja.second;
            for (const auto& punto : puntos) {
                mapa.agregar_caja(0, punto.x, punto.y, path);
                std::cout << "agrego una caja" << std::endl;
            }
            
        }

        mapa.procesado();
    }
    
    bool hubo_estado_nuevo = false;

    while (estado_juego.try_pop(ultimo_estado)) {
        for (Pato pato_juego: ultimo_estado.patos) {
            PatoInterfaz& pato_prueba = mapa.get_pato_con_id(pato_juego.get_id());
            pato_prueba.set_esta_vivo(pato_juego.esta_vivo());
            pato_prueba.actualizar_posicion(pato_juego.get_pos_x(), pato_juego.get_pos_y());
            pato_prueba.actualizar_estado(pato_juego.estado.get_estado_movimiento(), ESTADO_MOVIMIENTO);
            pato_prueba.actualizar_estado(pato_juego.estado.get_estado_salto(), ESTADO_SALTO);
            pato_prueba.actualizar_estado(pato_juego.get_direccion(), ESTADO_DIRECCION);
            if (pato_juego.get_direccion() == BYTE_NULO){
                pato_prueba.actualizar_estado(DIRECCION_DERECHA, ESTADO_DIRECCION);
            }
            pato_prueba.actualizar_estado(pato_juego.estado.get_estado_agachado(), ESTADO_PISO);
            pato_prueba.actualizar_equipamiento(pato_juego.tiene_arma(), ESTADO_ARMA);
            pato_prueba.actualizar_equipamiento(pato_juego.estado.get_estado_disparo(), ESTADO_BALAS);
            if (pato_juego.tiene_arma() == TOMAR_ARMA) {
                pato_prueba.actualizar_arma(pato_juego.get_arma()->get_tipo_arma());
                pato_prueba.actualizar_equipamiento(pato_juego.get_arma()->get_municion_disponible(), ESTADO_MUNICION);
            }
            // pato_prueba.actualizar_equipamiento(pato_juego.get_arma()->get_municion_disponible(), ESTADO_MUNICION);
            pato_prueba.actualizar_equipamiento(pato_juego.get_armadura_equipada(), ESTADO_ARMADURA);
            pato_prueba.actualizar_equipamiento(pato_juego.get_casco_equipado(), ESTADO_CASCO);
            //pato_prueba.get_arma().set_tipo_arma(pato_juego.get_arma().get_tipo_arma());
    
            //std::cout << "municion:" << static_cast<int>(pato_juego.get_arma()->get_municion_disponible()) << std::endl;
            if (pato_juego.get_id() == 4){
                std::cout << "pos x: " << static_cast<int>(pato_juego.get_pos_x()) << std::endl;
                std::cout << "pos y: " << static_cast<int>(pato_juego.get_pos_y()) << std::endl;
                std::cout << "direccion: " << static_cast<int>(pato_juego.get_direccion()) << std::endl;
                std::cout << "estado movimiento: " << static_cast<int>(pato_juego.estado.get_estado_movimiento()) << std::endl;
            }
        }
        hubo_estado_nuevo = true;
        //mostrar balas
        for (Bala balas_juego: ultimo_estado.balas) {
                mapa.agregar_bala("../resources/weapons/grenadePin.png", balas_juego.get_pos_x(),
                balas_juego.get_pos_y(), balas_juego.get_direccion());
                // pato_prueba.actualizar_posicion_bala(balas_juego.get_pos_x(), balas_juego.get_pos_y());
                // std::cout << "pos x bala:" << static_cast<int>(balas_juego.get_pos_x()) << std::endl;
                // std::cout << "pos y bala:" << static_cast<int>(balas_juego.get_pos_y()) << std::endl;
            }
    } 
    if (!hubo_estado_nuevo) {
        for (Pato pato_juego: ultimo_estado.patos) {
            PatoInterfaz& pato_prueba = mapa.get_pato_con_id(pato_juego.get_id());
            pato_prueba.actualizar_estado(BYTE_NULO, ESTADO_MOVIMIENTO);
            pato_prueba.actualizar_estado(BYTE_NULO, ESTADO_SALTO);
            //pato_prueba.actualizar_estado(BYTE_NULO, ESTADO_PISO);
        }
    }
    
}

