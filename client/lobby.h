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
    bool empezo_partida;

    void cargar_fondo();
    void cargar_boton(std::string& texto, SDL_Rect& boton_rect);
    void cargar_texto_boton(std::string& texto, SDL_Rect& boton_rect);
    void cerrar();

public:
    Lobby(SDL_Renderer* renderer);
    void dibujar();
    bool manejar_eventos();
    bool empezo() const;
};

#endif //LOBBY_H
