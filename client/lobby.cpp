#include "lobby.h"

Lobby::Lobby(SDL_Renderer* renderer): 
    renderer(renderer), 
    seleccion_cant_jugadores(false),
    empezo_partida(false),
    cant_jugadores(0) 
{
    fondo_texture = IMG_LoadTexture(renderer, "../resources/lobby/background_lobby.jpg");
    
    partida_nueva_rect = {200, 200, 350, 100};
    partida_existente_rect = {180, 400, 400, 100};
    
    un_jugador_rect = {200, 250, 300, 70};
    dos_jugadores_rect = {200, 370, 300, 70};
}

void Lobby::cargar_fondo(){
    SDL_RenderCopy(renderer, fondo_texture, NULL, NULL);
}

void Lobby::cargar_boton(std::string& texto, SDL_Rect& boton_rect){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &boton_rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &boton_rect);

    SDL_Color color = {255, 165, 0, 255};
    int tamanio = 24;
    cargar_texto(texto, boton_rect, color, tamanio);
}
    

void Lobby::cargar_texto(std::string& texto, SDL_Rect& boton_rect, SDL_Color& color_texto, int tamanio){
    /*TTF_Init();
    TTF_Font* font = TTF_OpenFont("../resources/lobby/lobby_font.TTF", 24);
    SDL_Color color_texto = {255, 165, 0, 255};
    SDL_Surface* surface_texto = TTF_RenderText_Solid(font, texto.c_str(), color_texto);
    SDL_Texture* texture_texto = SDL_CreateTextureFromSurface(renderer, surface_texto);*/
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }

    // Crear y renderizar el texto dentro del botón
    TTF_Font* font = TTF_OpenFont("../resources/lobby/lobby_font.TTF", tamanio);  // Abrir fuente (ajusta el tamaño)
    if (font == NULL) {
        std::cout << "Error loading font: " << TTF_GetError() << std::endl;
        return;
    }

    // Crear una superficie con el texto
    SDL_Surface* surface_texto = TTF_RenderText_Solid(font, texto.c_str(), color_texto);  // Texto a mostrar
    if (surface_texto == NULL) {
        std::cout << "Error creating text surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    // Convertir la superficie en una textura
    SDL_Texture* texture_texto = SDL_CreateTextureFromSurface(renderer, surface_texto);
    if (texture_texto == NULL) {
        std::cout << "Error creating text texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface_texto);
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect rect_texto = {
        boton_rect.x + (boton_rect.w - surface_texto->w) / 2,
        boton_rect.y + (boton_rect.h - surface_texto->h) / 2,
        surface_texto->w,
        surface_texto->h
    };
    
    SDL_RenderCopy(renderer, texture_texto, NULL, &rect_texto);

    SDL_DestroyTexture(texture_texto);
    SDL_FreeSurface(surface_texto);
    TTF_CloseFont(font);
    TTF_Quit();
}


void Lobby::dibujar() {
    SDL_RenderClear(renderer);
    
    cargar_fondo();

    if(seleccion_cant_jugadores){
        std::string texto_un_jugador = "One Player";
        cargar_boton(texto_un_jugador, un_jugador_rect);

        std::string texto_dos_jugadores = "Two Players";
        cargar_boton(texto_dos_jugadores, dos_jugadores_rect);
    } else {
        std::string nueva_partida_texto = "New Game";
        cargar_boton(nueva_partida_texto, partida_nueva_rect);

        std::string partida_existente_texto = "Join Existing Game";
        cargar_boton(partida_existente_texto, partida_existente_rect);
    }

    SDL_RenderPresent(renderer);
}

void Lobby::manejar_eventos() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            cerrar();
            return;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            // Check cantidad de jugadores
            if (seleccion_cant_jugadores) {
                if (x >= un_jugador_rect.x && x <= un_jugador_rect.x + un_jugador_rect.w &&
                    y >= un_jugador_rect.y && y <= un_jugador_rect.y + un_jugador_rect.h) {
                     // Single player selected
                    cant_jugadores = 1;
                    empezo_partida = true; 
                }

                if (x >= dos_jugadores_rect.x && x <= dos_jugadores_rect.x + dos_jugadores_rect.w &&
                    y >= dos_jugadores_rect.y && y <= dos_jugadores_rect.y + dos_jugadores_rect.h) {
                      // Multiplayer selected
                    cant_jugadores = 2;
                    empezo_partida = true;
                }
            }

            // check modo de juego
            if (x >= partida_nueva_rect.x && x <= partida_nueva_rect.x + partida_nueva_rect.w &&
                y >= partida_nueva_rect.y && y <= partida_nueva_rect.y + partida_nueva_rect.h) {
                seleccion_cant_jugadores = true;
            }

            if (x >= partida_existente_rect.x && x <= partida_existente_rect.x + partida_existente_rect.w &&
                y >= partida_existente_rect.y && y <= partida_existente_rect.y + partida_existente_rect.h) {
                //algo para decir que se unio a una partida existente
            }

        }
    }

    //return empezo_partida;
}

bool Lobby::empezo() const{
    return empezo_partida;
}

int Lobby::cantidad_jugadores() const{
    return cant_jugadores;
}


void Lobby::cargar_pantalla(std::vector<SDL_Texture*>& texturas_ganador) {
    // Load the surface for the winner screen
    SDL_Surface* ganador_surface = IMG_Load("../resources/winner.png");
    if (!ganador_surface) {
        SDL_Log("Failed to load image: %s", SDL_GetError());
        return;
    }

    int frame_width = 152;
    int frame_height = 275;
    for (int i = 0; i < 6; i++) {
        SDL_Rect frame_rect = { i * frame_width, 0, frame_width, frame_height };
        SDL_Surface* frame_surface = SDL_CreateRGBSurface(0, frame_width, frame_height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

        SDL_BlitSurface(ganador_surface, &frame_rect, frame_surface, nullptr);

        SDL_Texture* frame_texture = SDL_CreateTextureFromSurface(renderer, frame_surface);
        texturas_ganador.push_back(frame_texture);

        SDL_FreeSurface(frame_surface);
    }

    SDL_FreeSurface(ganador_surface);

}

void Lobby::mostrar_pantalla_ganador(int it) {
    static std::vector<SDL_Texture*> texturas_ganador;
    static bool loaded = false;
    if (!loaded) {
        cargar_pantalla(texturas_ganador);
        loaded = true;
    }

    SDL_Event event;
    bool quit = false;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            cerrar();
            quit = true;
            break;
        }
    }

    SDL_RenderClear(renderer);
    SDL_Texture* fondo_texture = IMG_LoadTexture(renderer, "../resources/backgrounds/forest.png");
    SDL_RenderCopy(renderer, fondo_texture, NULL, NULL);
    std::string texto = "YOU WIN!";
    SDL_Rect rect_texto = { 520, 100, 200, 100 };
    SDL_Color color = { 240, 240, 0, 255 };
    int tamanio = 36;
    cargar_texto(texto, rect_texto, color, tamanio);
    SDL_Rect dest_rect = { 475, 150, 300, 400 };
    SDL_RenderCopy(renderer, texturas_ganador[it % 6], nullptr, &dest_rect);

    SDL_RenderPresent(renderer);

    if (quit) return;
}
    


void Lobby::cerrar() {
    SDL_DestroyTexture(fondo_texture);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}