#include "lobby.h"

Lobby::Lobby(SDL_Renderer* renderer): 
    renderer(renderer), 
    rects_ids_partidas(),
    cant_jugadores(0),
    estado(EstadoLobby::INICIAL),
    partidas()
{
    fondo_texture = IMG_LoadTexture(renderer, "../resources/lobby/background_lobby.jpg");
    
    partida_nueva_rect = {200, 200, 350, 100};
    partida_existente_rect = {180, 400, 400, 100};
    
    un_jugador_rect = {200, 250, 300, 70};
    dos_jugadores_rect = {200, 370, 300, 70};

    iniciar_partida_rect = {450, 400, 350, 100};
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


void Lobby::dibujar(std::list<uint8_t>& partidas) {
    SDL_RenderClear(renderer);
    
    cargar_fondo();

    if(estado == EstadoLobby::INICIAL){
        std::string texto_un_jugador = "One Player";
        cargar_boton(texto_un_jugador, un_jugador_rect);

        std::string texto_dos_jugadores = "Two Players";
        cargar_boton(texto_dos_jugadores, dos_jugadores_rect);
    } else if (estado == EstadoLobby::MODO_JUEGO) {
        std::string nueva_partida_texto = "New Game";
        cargar_boton(nueva_partida_texto, partida_nueva_rect);

        std::string partida_existente_texto = "Join Existing Game";
        cargar_boton(partida_existente_texto, partida_existente_rect);
    } else if (estado == EstadoLobby::INICIAR_PARTIDA){
        
        SDL_Texture* fondo = IMG_LoadTexture(renderer, "../resources/lobby/background_lobby2.jpg");
        SDL_RenderCopy(renderer, fondo, NULL, NULL);

        std::string iniciar_partida_texto = "Start Game";
        cargar_boton(iniciar_partida_texto, iniciar_partida_rect);
    } else if (estado == EstadoLobby::UNIRSE_A_PARTIDA){
        SDL_Texture* fondo = IMG_LoadTexture(renderer, "../resources/lobby/background_lobby2.jpg");
        SDL_RenderCopy(renderer, fondo, NULL, NULL);

        for (uint8_t& id_partida : partidas) {
            int id = static_cast<int>(id_partida);
            SDL_Rect rect;
            if(id > 0){
                SDL_Rect rect_anterior = rects_ids_partidas[id - 1];
                rect = {rect_anterior.x + 150, rect_anterior.y, 100, 100};

            } else {
                rect = {200, 200, 100, 100};
            }
            rects_ids_partidas[id] = rect;
            std::string id_texto = std::to_string(id);
            cargar_boton(id_texto, rect);
        }
    } else if (estado == EstadoLobby::ESPERAR_INICIO_PARTIDA){
        SDL_Texture* fondo = IMG_LoadTexture(renderer, "../resources/lobby/background_lobby2.jpg");
        SDL_RenderCopy(renderer, fondo, NULL, NULL);

        std::string texto = "Waiting for the game to start...";
        SDL_Rect rect_texto = { 475, 350, 400, 100 };
        SDL_Color color = { 155, 255, 255, 255 };
        int tamanio = 36;
        cargar_texto(texto, rect_texto, color, tamanio);
    }

    SDL_RenderPresent(renderer);
}

PedidoJugador Lobby::manejar_eventos() {
    SDL_Event event;
    PedidoJugador pedido;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            cerrar();
            return pedido;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            if(estado == EstadoLobby::MODO_JUEGO){
                if (x >= partida_nueva_rect.x && x <= partida_nueva_rect.x + partida_nueva_rect.w &&
                    y >= partida_nueva_rect.y && y <= partida_nueva_rect.y + partida_nueva_rect.h) {
                    pedido.partida_nueva();

                    estado = EstadoLobby::INICIAR_PARTIDA;
                }

                if (x >= partida_existente_rect.x && x <= partida_existente_rect.x + partida_existente_rect.w &&
                    y >= partida_existente_rect.y && y <= partida_existente_rect.y + partida_existente_rect.h) {
                    estado = EstadoLobby::UNIRSE_A_PARTIDA;
                }
            } else if (estado == EstadoLobby::INICIAL){
                if (x >= un_jugador_rect.x && x <= un_jugador_rect.x + un_jugador_rect.w &&
                    y >= un_jugador_rect.y && y <= un_jugador_rect.y + un_jugador_rect.h) {
                    pedido.juega_uno_solo();
                    cant_jugadores = 1;
                    estado = EstadoLobby::MODO_JUEGO;
                }

                if (x >= dos_jugadores_rect.x && x <= dos_jugadores_rect.x + dos_jugadores_rect.w &&
                    y >= dos_jugadores_rect.y && y <= dos_jugadores_rect.y + dos_jugadores_rect.h) {
                    pedido.juegan_dos_personas();
                    cant_jugadores = 2;
                    estado = EstadoLobby::MODO_JUEGO;
                }
            } else if (estado == EstadoLobby::INICIAR_PARTIDA){
                if (x >= iniciar_partida_rect.x && x <= iniciar_partida_rect.x + iniciar_partida_rect.w &&
                    y >= iniciar_partida_rect.y && y <= iniciar_partida_rect.y + iniciar_partida_rect.h) {
                    pedido.iniciar_partida();
                }
            } else if (estado == EstadoLobby::UNIRSE_A_PARTIDA){
                for (auto& rect : rects_ids_partidas) {
                    if (x >= rect.second.x && x <= rect.second.x + rect.second.w &&
                        y >= rect.second.y && y <= rect.second.y + rect.second.h) {
                        pedido.unirse_a_partida_con_id(rect.first);
                        estado = EstadoLobby::ESPERAR_INICIO_PARTIDA;
                        return pedido;  
                    }
                }
            }
        }
    }

    return pedido;
}

bool Lobby::empezo() const{
    if(estado == EstadoLobby::FINALIZADO){
        return true;
    }
    return false;
}

int Lobby::cantidad_jugadores() const{
    return cant_jugadores;
}

void Lobby::actualizar_partidas(std::list<Partida>& partidas) {
    this->partidas = partidas;
}

void Lobby::partida_iniciada() {
    estado = EstadoLobby::FINALIZADO;
}


void Lobby::cargar_pantalla(std::vector<SDL_Texture*>& texturas_ganador, std::string path, 
            int cant_frames, int frame_width, int frame_height, int offset_x, int offset_y) {
    // Load the surface for the winner screen
    SDL_Surface* ganador_surface = IMG_Load(path.c_str());
    if (!ganador_surface) {
        SDL_Log("Failed to load image: %s", SDL_GetError());
        return;
    }

    for (int i = 0; i < cant_frames; i++) {
        SDL_Rect frame_rect = { i * frame_width + offset_x , offset_y, frame_width, frame_height };
        SDL_Surface* frame_surface = SDL_CreateRGBSurface(0, frame_width, frame_height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

        SDL_BlitSurface(ganador_surface, &frame_rect, frame_surface, nullptr);

        SDL_Texture* frame_texture = SDL_CreateTextureFromSurface(renderer, frame_surface);
        texturas_ganador.push_back(frame_texture);

        SDL_FreeSurface(frame_surface);
    }

    SDL_FreeSurface(ganador_surface);

}

SDL_Color Lobby::color_pato(int index) {
    if(index == 1){
        index = 30;
    } else if (index == 2){
        index = 35;
    }
    uint8_t r = (index * 50) % 256;
    uint8_t g = ((index + 1) * 70) % 256;
    uint8_t b = ((index + 2) * 90) % 256;
    return {r, g, b, 255};
}

void Lobby::mostrar_pato_identificatorio(uint16_t id1, uint16_t id2){
    SDL_Texture* fondo = IMG_LoadTexture(renderer, "../resources/lobby/background_lobby2.jpg");
    SDL_RenderCopy(renderer, fondo, NULL, NULL);
    SDL_Color color_texto = { 255, 255, 255, 255 };
    
    std::string texto1 = "Player 1 duck color is ";
    SDL_Rect rect_texto1 = { 200, 200, 200, 100 };
    cargar_texto(texto1, rect_texto1, color_texto, 24);

    SDL_Rect rect_color1 = { 530, 215, 50, 50 };
    SDL_Color color_pato1 = color_pato(id1);
    SDL_SetRenderDrawColor(renderer, color_pato1.r, color_pato1.g, color_pato1.b, color_pato1.a);
    SDL_RenderFillRect(renderer, &rect_color1);
    
    if(id2 != 0){
        std::string texto2 = "Player 2 duck color is ";
        SDL_Rect rect_texto2 = { 200, 300, 200, 100 };
        cargar_texto(texto2, rect_texto2, color_texto, 24);

        SDL_Rect rect_color2 = { 530, 315, 50, 50 };
        SDL_Color color_pato2 = color_pato(id2);
        SDL_SetRenderDrawColor(renderer, color_pato2.r, color_pato2.g, color_pato2.b, color_pato2.a);
        SDL_RenderFillRect(renderer, &rect_color2);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
}

void Lobby::mostrar_pantalla_ganador(int it) {
    static std::vector<SDL_Texture*> texturas_ganador;
    static bool loaded = false;
    if (!loaded) {
        std::string path = "../resources/winner.png";
        cargar_pantalla(texturas_ganador, path, 6, 136, 275, 0, 0);
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
    SDL_Delay(100);
    SDL_RenderPresent(renderer);

    if (quit) return;
}

void Lobby::mostrar_pantalla_perdedor(){
    static std::vector<SDL_Texture*> texturas_ganador;
    static bool loaded = false;
    if (!loaded) {
        std::string path = "../resources/Grey-Duck.png";
        cargar_pantalla(texturas_ganador, path, 4, 32, 32, 1, 71);
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
    SDL_Texture* grave_texture = IMG_LoadTexture(renderer, "../resources/grave.png");
    SDL_Rect rect_grave = { 475, 250, 275, 275 };
    SDL_RenderCopy(renderer, grave_texture, NULL, &rect_grave);
    std::string texto = "YOU LOSE :(";
    SDL_Rect rect_texto = { 520, 100, 200, 100 };
    SDL_Color color = { 0, 0, 0, 255 };
    int tamanio = 36;
    cargar_texto(texto, rect_texto, color, tamanio);
    SDL_Rect dest_rect = { 500, 200, 250, 350 };
    SDL_RenderCopy(renderer, texturas_ganador[1], nullptr, &dest_rect);

    SDL_RenderPresent(renderer);

    if (quit) return;

}
    


void Lobby::cerrar() {
    SDL_DestroyTexture(fondo_texture);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}