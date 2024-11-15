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
#include "disparo.h"
#include "mapa_interfaz.h"
#include <set>

class InterfazGrafica {
    private:
    Queue<ComandoGrafica>& comandos_cliente;
    Queue<EstadoJuego>& estado_juego;
    bool correr_programa;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;


    void manejar_eventos();
    void obtener_estado_juego(MapaInterfaz& mapa);

    public:
    InterfazGrafica(Queue<ComandoGrafica>& cola_comandos, Queue<EstadoJuego>& cola_estado_juego);
    void iniciar();

    void drop_rest(float& tiempo_ultimo_frame, int& it);
};

#endif  
