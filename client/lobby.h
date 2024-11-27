#ifndef LOBBY_H
#define LOBBY_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <functional>

class Lobby {
private:
    SDL_Renderer* renderer;
    SDL_Texture* fondo_texture;
    SDL_Texture* boton_texture;
    SDL_Rect partida_nueva_rect;
    SDL_Rect partida_existente_rect;
    SDL_Rect un_jugador_rect;
    SDL_Rect dos_jugadores_rect;
    bool seleccion_cant_jugadores;
    bool empezo_partida;
    int cant_jugadores;


    void cargar_fondo();
    void cargar_boton(std::string& texto, SDL_Rect& boton_rect);
    void cargar_texto(std::string& texto, SDL_Rect& boton_rect, SDL_Color& color, int tamanio);
    void cargar_pantalla(std::vector<SDL_Texture*>& texturas_ganador, std::string path, 
                    int cant_frames, int frame_width, int frame_height, int offset_x, int offset_y);
    void cerrar();

public:
    Lobby(SDL_Renderer* renderer);
    void dibujar();
    void manejar_eventos();
    bool empezo() const;
    int cantidad_jugadores() const;
    void mostrar_pantalla_ganador(int it);
    void mostrar_pantalla_perdedor();
};

#endif //LOBBY_H
