#include "lobby.h"

Lobby::Lobby(SDL_Renderer* renderer): renderer(renderer), empezo_partida(false) {
    fondo_texture = IMG_LoadTexture(renderer, "../resources/lobby/background_lobby.jpg");
    partida_nueva_rect = {200, 200, 350, 100};
}

void Lobby::cargar_fondo(){
    SDL_RenderCopy(renderer, fondo_texture, NULL, NULL);
}

void Lobby::cargar_boton(std::string& texto, SDL_Rect& boton_rect){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &boton_rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &boton_rect);

    cargar_texto_boton(texto, boton_rect);
}
    

void Lobby::cargar_texto_boton(std::string& texto, SDL_Rect& boton_rect){
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("../resources/lobby/lobby_font.TTF", 24);
    SDL_Color color_texto = {255, 165, 0, 255};
    SDL_Surface* surface_texto = TTF_RenderText_Solid(font, texto.c_str(), color_texto);
    SDL_Texture* texture_texto = SDL_CreateTextureFromSurface(renderer, surface_texto);

    SDL_Rect rect_texto = {
        boton_rect.x + (boton_rect.w - surface_texto->w) / 2,
        boton_rect.y + (boton_rect.h - surface_texto->h) / 2,
        surface_texto->w,
        surface_texto->h
    };
    
    SDL_RenderCopy(renderer, texture_texto, NULL, &rect_texto);
}


void Lobby::dibujar() {
    SDL_RenderClear(renderer);
    
    cargar_fondo();

    std::string texto_boton = "Start New Game";
    cargar_boton(texto_boton, partida_nueva_rect);

    SDL_RenderPresent(renderer);
}

bool Lobby::manejar_eventos() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            cerrar();
            return false;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            if (x >= partida_nueva_rect.x && x <= partida_nueva_rect.x + partida_nueva_rect.w &&
                y >= partida_nueva_rect.y && y <= partida_nueva_rect.y + partida_nueva_rect.h) {
                empezo_partida = true;
            }
        }
    }
    return empezo_partida;
}

bool Lobby::empezo() const{
    return empezo_partida;
}

void Lobby::cerrar() {
    SDL_DestroyTexture(fondo_texture);
    SDL_DestroyTexture(boton_texture);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}