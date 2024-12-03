#ifndef LOBBY_H
#define LOBBY_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <functional>
#include "../common/common_pedido_jugador.h"
#include "../common/common_lobby_info.h"
#include <list>
#include <map>

enum EstadoLobby {
    INICIAL,
    MODO_JUEGO,
    INICIAR_PARTIDA,
    UNIRSE_A_PARTIDA,
    ESPERAR_INICIO_PARTIDA,
    FINALIZADO
};

class Lobby {
private:
    SDL_Renderer* renderer;
    SDL_Texture* fondo_texture;
    SDL_Texture* boton_texture;
    SDL_Rect partida_nueva_rect;
    SDL_Rect partida_existente_rect;
    SDL_Rect un_jugador_rect;
    SDL_Rect dos_jugadores_rect;
    SDL_Rect id_partida_rect;
    SDL_Rect iniciar_partida_rect;
    std::map<uint16_t, SDL_Rect> rects_ids_partidas;
    int cant_jugadores;
    EstadoLobby estado;
    std::list<Partida> partidas;


    void cargar_fondo();
    void cargar_boton(std::string& texto, SDL_Rect& boton_rect);
    void cargar_texto(std::string& texto, SDL_Rect& boton_rect, SDL_Color& color, int tamanio);
    void cargar_pantalla(std::vector<SDL_Texture*>& texturas_ganador, std::string path, 
                    int cant_frames, int frame_width, int frame_height, int offset_x, int offset_y);
    SDL_Color color_pato(int index);
    void cerrar();

public:
    Lobby(SDL_Renderer* renderer);
    void dibujar(std::list<uint8_t>& partidas);
    PedidoJugador manejar_eventos();
    bool empezo() const;
    int cantidad_jugadores() const;
    void actualizar_partidas(std::list<Partida>& partidas);
    void partida_iniciada();
    void mostrar_pato_identificatorio(uint16_t id1, uint16_t id2);
    void mostrar_pantalla_ganador(int it, uint16_t id_ganador);
    void mostrar_pantalla_perdedor();
};

#endif //LOBBY_H
