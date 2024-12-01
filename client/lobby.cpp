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

    id_partida_rect = {450, 200, 350, 100};
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

    cargar_texto_boton(texto, boton_rect);
}
    

void Lobby::cargar_texto_boton(std::string& texto, SDL_Rect& boton_rect){
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
    TTF_Font* font = TTF_OpenFont("../resources/lobby/lobby_font.TTF", 24);  // Abrir fuente (ajusta el tamaño)
    if (font == NULL) {
        std::cout << "Error loading font: " << TTF_GetError() << std::endl;
        return;
    }

    // Crear una superficie con el texto
    SDL_Color color_texto = {255, 165, 0, 255};  // Blanco para el texto (puedes cambiar el color)
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
        
        std::string id_partida_texto = "ID Partida: ";
        //id_partida_texto += std::to_string(partidas.back().obtener_id());
        cargar_boton(id_partida_texto, id_partida_rect);

        std::string iniciar_partida_texto = "Start Game";
        cargar_boton(iniciar_partida_texto, iniciar_partida_rect);
    } else if (estado == EstadoLobby::UNIRSE_A_PARTIDA){
        SDL_Texture* fondo = IMG_LoadTexture(renderer, "../resources/lobby/background_lobby2.jpg");
        SDL_RenderCopy(renderer, fondo, NULL, NULL);

        for (Partida& partida : partidas) {
            if(!partida.esta_iniciada()){
                int id = partida.obtener_id();
                SDL_Rect rect;
                if(id > 0){
                    SDL_Rect rect_anterior = rects_ids_partidas[id - 1];
                    rect = {rect_anterior.x + 100, rect_anterior.y, 100, 100};

                } else {
                    rect = {200, 200, 100, 100};
                }
                rects_ids_partidas[partida.obtener_id()] = rect;
                std::string id_texto = std::to_string(partida.obtener_id());
                cargar_boton(id_texto, rect);
            }
        }

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
                // check modo de juego
                if (x >= partida_nueva_rect.x && x <= partida_nueva_rect.x + partida_nueva_rect.w &&
                    y >= partida_nueva_rect.y && y <= partida_nueva_rect.y + partida_nueva_rect.h) {
                    pedido.partida_nueva();

                    estado = EstadoLobby::INICIAR_PARTIDA;
                }

                if (x >= partida_existente_rect.x && x <= partida_existente_rect.x + partida_existente_rect.w &&
                    y >= partida_existente_rect.y && y <= partida_existente_rect.y + partida_existente_rect.h) {
                    //pedido.unirse_a_partida_con_id(1);
                    estado = EstadoLobby::UNIRSE_A_PARTIDA;
                    //algo para decir que se unio a una partida existente
                }
            } else if (estado == EstadoLobby::INICIAL){
                // Check cantidad de jugadores
                if (x >= un_jugador_rect.x && x <= un_jugador_rect.x + un_jugador_rect.w &&
                    y >= un_jugador_rect.y && y <= un_jugador_rect.y + un_jugador_rect.h) {
                     // Single player selected
                    pedido.juega_uno_solo();
                    cant_jugadores = 1;
                    estado = EstadoLobby::MODO_JUEGO;
                     //esta data deberia llegar del servidor
                }

                if (x >= dos_jugadores_rect.x && x <= dos_jugadores_rect.x + dos_jugadores_rect.w &&
                    y >= dos_jugadores_rect.y && y <= dos_jugadores_rect.y + dos_jugadores_rect.h) {
                      // Multiplayer selected
                    pedido.juegan_dos_personas();
                    cant_jugadores = 2;
                    estado = EstadoLobby::MODO_JUEGO;
                }
            } else if (estado == EstadoLobby::INICIAR_PARTIDA){
                if (x >= iniciar_partida_rect.x && x <= iniciar_partida_rect.x + iniciar_partida_rect.w &&
                    y >= iniciar_partida_rect.y && y <= iniciar_partida_rect.y + iniciar_partida_rect.h) {
                    pedido.iniciar_partida();
                    estado = EstadoLobby::FINALIZADO;
                }
            } else if (estado == EstadoLobby::UNIRSE_A_PARTIDA){
                for (auto& rect : rects_ids_partidas) {
                    if (x >= rect.second.x && x <= rect.second.x + rect.second.w &&
                        y >= rect.second.y && y <= rect.second.y + rect.second.h) {
                        pedido.unirse_a_partida_con_id(rect.first);
                        std::cout << "Unido a la partida con ID: " << rect.first << std::endl;
                        estado = EstadoLobby::FINALIZADO;
                        return pedido;  
                    }
                }
            }
        }

        /*// Handle text input when in the UNIRSE_A_PARTIDA state
        if (estado == EstadoLobby::UNIRSE_A_PARTIDA) {
            std::string user_input;
            if (event.type == SDL_KEYDOWN) {
                // Handle backspace to delete the last character
                if (event.key.keysym.sym == SDLK_BACKSPACE && !user_input.empty()) {
                    user_input.pop_back();
                }
                // Handle the Enter key to confirm input and send it as a request
                else if (event.key.keysym.sym == SDLK_RETURN && !user_input.empty()) {
                    pedido.unirse_a_partida_con_id(std::stoi(user_input));
                    std::cout << "Unido a la partida con ID: " << user_input << std::endl;
                    user_input.clear();  // Clear the input after using it
                    estado = EstadoLobby::FINALIZADO;
                    return pedido;  // Send the request
                }
            }
            // Handle text input events
            else if (event.type == SDL_TEXTINPUT) {
                user_input += event.text.text;  // Append new text to the input
            }
        }*/
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

void Lobby::cerrar() {
    SDL_DestroyTexture(fondo_texture);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}