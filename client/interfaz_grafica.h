#ifndef INTERFAZ_GRAFICA_H
#define INTERFAZ_GRAFICA_H

#include <exception>
#include <iostream>
#include <vector>
#include "pato_interfaz.h"
#include "fondo_interfaz.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "cliente_comando.h"
#include "../common/common_queue.h"
#include "../common/common_estado_juego.h"
#include "mapa_interfaz.h"
#include <set>
#include <unordered_map>
#include "../common/common_pedido_jugador.h"

class InterfazGrafica {
    private:
    Queue<ComandoGrafica>& comandos_cliente;
    Queue<EstadoJuego>& estado_juego;
    bool correr_programa;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;

    void iniciar_audio(std::string audio_path);
    void manejar_eventos_por_jugador(ComandoGrafica& comando_cliente, SDL_Event& evento, 
                        const std::unordered_map<SDL_Keycode, std::string>& key_map, int jugador_id, bool es_presionado);
    void manejar_eventos(std::set<SDL_Keycode>& keysHeld, int cant_jugadores, int id1, int id2);
    void procesar_mapa(MapaInterfaz& mapa, EstadoJuego& ultimo_estado, bool& mapa_procesado);
    void obtener_estado_juego(MapaInterfaz& mapa, bool& mapa_procesado, uint8_t& id_partida);

    public:
    InterfazGrafica(Queue<ComandoGrafica>& cola_comandos, Queue<EstadoJuego>& cola_estado_juego);
    void iniciar();

    void drop_rest(float& tiempo_ultimo_frame, int& it);
};

#endif  
