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
#define INICIAR_PARTIDA 0X01


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

    int it = 0;
    float tiempo_ultimo_frame = SDL_GetTicks();
    uint16_t id1 = 0;
    uint16_t id2 = 0;
    uint8_t id_partida = 0;

    EstadoJuego ultimo_estado = estado_juego.pop();

    id1 = ultimo_estado.id_jugador;
    id_partida = ultimo_estado.id_partida;

    // std::cout << "ID CLIENTE ES: " << static_cast<int>(id1) << std::endl;
    // std::cout << "ID PARTIDA ES: " << static_cast<int>(id_partida) << std::endl;

    Lobby lobby(renderer.Get());


     MapaInterfaz mapa_a_jugar(renderer, id1);
    //bool mapa_recibido = false;
    bool mapa_procesado = false;

    while (!lobby.empezo()) {
        ComandoGrafica comando_cliente;
        comando_cliente.pedido = lobby.manejar_eventos();
        comando_cliente.jugador_id = id1;
        comando_cliente.tecla = NO_ABAJO; //algo arbitrario no relevante
        comandos_cliente.push(comando_cliente);


        
        
        while (estado_juego.try_pop(ultimo_estado)) {
            if (id_partida != ultimo_estado.id_partida){
                id_partida = ultimo_estado.id_partida;
            }
            if (ultimo_estado.partida_iniciada == INICIAR_PARTIDA){
                std::cout << "tengo que empezar la partida" << std::endl;
                lobby.partida_iniciada();
                procesar_mapa(mapa_a_jugar, ultimo_estado, mapa_procesado);
                break;
            }
        }
        lobby.dibujar(ultimo_estado.partidas);
        // std::cout << "ID PARTIDA NUEVO ES: " << static_cast<int>(id_partida) << std::endl;
        drop_rest(tiempo_ultimo_frame, it);
    }

    int cant_jugadores = lobby.cantidad_jugadores();
    if(cant_jugadores == 2){
        id2 = id1 + 1;
    }

    std::string audio_fondo_path = "../resources/sounds/background_music.mp3";
    iniciar_audio(audio_fondo_path);
    std::set<SDL_Keycode> keysHeld;
    it = 0;
    tiempo_ultimo_frame = SDL_GetTicks();

    while (correr_programa) {
        renderer.Clear();
        manejar_eventos(keysHeld, cant_jugadores, static_cast<int>(id1), static_cast<int>(id2));
        obtener_estado_juego(mapa_a_jugar, mapa_procesado, id_partida);
        mapa_a_jugar.dibujar(it);
        renderer.Present();
            
        //ahora calculamos cuanto tardamos en hacer todo, si nos pasamos, drop & rest.
        drop_rest(tiempo_ultimo_frame, it);
    }
    
    //mostrar pantalla de ganador o perdedor 
    while(true) {
        renderer.Clear();
        lobby.mostrar_pantalla_ganador(it);
        //lobby.mostrar_pantalla_perdedor();
        drop_rest(tiempo_ultimo_frame, it);
    }

    //Mix_FreeMusic(music);
    IMG_Quit();
    SDL_Quit();
    Mix_CloseAudio();
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
        //std::cout << "pierdo frames" << std::endl;
    }
    SDL_Delay(descansar);
    it += 1;
    tiempo_ultimo_frame = tiempo_actual;
}

void InterfazGrafica::manejar_eventos_por_jugador(ComandoGrafica& comando_cliente, SDL_Event& evento, 
        const std::unordered_map<SDL_Keycode, std::string>& key_map, int jugador_id, bool es_presionado) {
    auto it = key_map.find(evento.key.keysym.sym);
    if (it != key_map.end()) {
        comando_cliente.tecla = es_presionado ? it->second : "!" + it->second; 
        comando_cliente.jugador_id = jugador_id;
        comandos_cliente.push(comando_cliente);
    }
}

void InterfazGrafica::manejar_eventos(std::set<SDL_Keycode>& keysHeld, int cant_jugadores, 
                                            int id1, int id2) {
    SDL_Event evento;

    std::unordered_map<SDL_Keycode, std::string> key_map_jugador_1 = {
        { SDLK_d, DERECHA }, { SDLK_a, IZQUIERDA },
        { SDLK_w, ARRIBA }, { SDLK_s, ABAJO },
        { SDLK_SPACE, SALTO }, { SDLK_f, DISPARO },
        { SDLK_g, AGARRAR_ARMA }
    };

    std::unordered_map<SDL_Keycode, std::string>key_map_jugador_2 = {
        { SDLK_RIGHT, DERECHA }, { SDLK_LEFT, IZQUIERDA },
        { SDLK_UP, ARRIBA }, { SDLK_DOWN, ABAJO },
        { SDLK_KP_0, SALTO }, { SDLK_KP_1, DISPARO },
        { SDLK_KP_2, AGARRAR_ARMA }
    };

    while (SDL_PollEvent(&evento)) {
        ComandoGrafica comando_cliente;

        if (evento.type == SDL_QUIT) {
            correr_programa = false;

        } else if (evento.type == SDL_KEYDOWN) {
            if (keysHeld.find(evento.key.keysym.sym) == keysHeld.end()) {
                // Check for escape key
                if (evento.key.keysym.sym == SDLK_ESCAPE) {
                    correr_programa = false;
                }
                manejar_eventos_por_jugador(comando_cliente, evento, key_map_jugador_1, id1, true);
                if (cant_jugadores == 2) {
                    manejar_eventos_por_jugador(comando_cliente, evento, key_map_jugador_2, id2, true);
                }

                // Mark this key as held
                keysHeld.insert(evento.key.keysym.sym);
            }
        } else if (evento.type == SDL_KEYUP) {
            manejar_eventos_por_jugador(comando_cliente, evento, key_map_jugador_1, id1, false);
            if (cant_jugadores == 2) {
                manejar_eventos_por_jugador(comando_cliente, evento, key_map_jugador_2, id2, false);
            }

            // Remove the released key from the held keys set
            keysHeld.erase(evento.key.keysym.sym);
        }
    }
}

void InterfazGrafica::procesar_mapa(MapaInterfaz& mapa, EstadoJuego& ultimo_estado, bool& mapa_procesado) {
    Mapa mapa_a_jugar = ultimo_estado.mapa;
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
     
        // procesar cajas 
        std::map<std::string, std::vector<SDL_Point>> cajas = mapa_a_jugar.getCajas();
        for (const auto& textura_punto : cajas) {
            std::string path_textura = textura_punto.first;
            std::vector<SDL_Point> puntos = textura_punto.second;
            for (const auto& punto : puntos) {
                mapa.agregar_caja(punto.x, punto.y);
            }
        }
      
        // procesar equipamiento
        std::map<std::string, std::vector<SDL_Point>> equipamientos = mapa_a_jugar.getEquipamiento();
        for (const auto& equipamiento : equipamientos) {
            std::string equipamiento_path = equipamiento.first;
            std::vector<SDL_Point> puntos = equipamiento.second;
            for (const auto& punto : puntos) {
                mapa.agregar_equipamiento(equipamiento_path, punto.x, punto.y);
            }
        }
        mapa_procesado = true;
}

void InterfazGrafica::obtener_estado_juego(MapaInterfaz& mapa, bool& mapa_procesado, uint8_t& id_partida) {
    
    EstadoJuego ultimo_estado;  
    
    if (!estado_juego.try_pop(ultimo_estado)){
        return;
    }
    mapa_procesado = true;

    while (estado_juego.try_pop(ultimo_estado)) {
        if (ultimo_estado.id_partida == id_partida){

            for (Pato pato_juego: ultimo_estado.patos) {
                PatoInterfaz& pato_prueba = mapa.get_pato_con_id(pato_juego.get_id());
                pato_prueba.set_esta_vivo(pato_juego.esta_vivo());
                pato_prueba.actualizar_posicion(pato_juego.get_pos_x(), pato_juego.get_pos_y());
                
                pato_prueba.actualizar_estado(pato_juego.estado.get_estado_movimiento(), ESTADO_MOVIMIENTO);
                pato_prueba.actualizar_estado(pato_juego.estado.get_estado_salto(), ESTADO_SALTO);
                pato_prueba.actualizar_estado(pato_juego.estado.get_estado_agachado(), ESTADO_PISO);
                
                pato_prueba.actualizar_estado(pato_juego.get_direccion(), ESTADO_DIRECCION);
                if (pato_juego.get_direccion() == BYTE_NULO){
                    pato_prueba.actualizar_estado(DIRECCION_DERECHA, ESTADO_DIRECCION);
                }
            
                pato_prueba.actualizar_equipamiento(pato_juego.tiene_arma(), ESTADO_ARMA);
                pato_prueba.actualizar_equipamiento(pato_juego.estado.get_estado_disparo(), ESTADO_BALAS);
                if (pato_juego.tiene_arma() == TOMAR_ARMA) {
                    pato_prueba.actualizar_arma(pato_juego.get_arma().get_tipo_arma());
                }

                pato_prueba.actualizar_equipamiento(pato_juego.get_armadura_equipada(), ESTADO_ARMADURA);
                pato_prueba.actualizar_equipamiento(pato_juego.get_casco_equipado(), ESTADO_CASCO);
            }

        //mostrar balas
        for (Bala balas_juego: ultimo_estado.balas) {
            mapa.agregar_bala(balas_juego.get_tipo_arma(), balas_juego.get_pos_x(),
            balas_juego.get_pos_y(), balas_juego.get_direccion());
            
        }
        //verificar cajas agarradas
        for (Caja caja : ultimo_estado.cajas){
            if (caja.get_esta_vacia()){
            mapa.caja_recogida(caja.get_pos_x(), caja.get_pos_y());
            }
        }
        //verificar equipamiento agarrado
        for (Arma arma : ultimo_estado.armas){
           if (arma.get_se_agarro()){
               mapa.equip_recogido(arma.get_pos_x(), arma.get_pos_y());
           }
        }
        for (Proteccion armadura : ultimo_estado.armaduras){
           if (armadura.get_se_agarro()){
               mapa.equip_recogido(armadura.get_pos_x(), armadura.get_pos_y());
           }
        }
    } 
    }
}
