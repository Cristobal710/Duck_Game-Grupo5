#include "editor.h"
#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280

Editor::Editor(): window("Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE),
                  renderer(window, -1, SDL_RENDERER_ACCELERATED),   
boton_fondo(10, 10, 180, 50, "Elegir Fondo"),
boton_tiles(200, 10, 180, 50, "Elegir Tiles"),
mostrar_fondos_disponibles(false), mostrar_tiles_disponibles(false),
tiles_seleccionados() 
{}


void Editor::iniciar_editor() {
    
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    
    SDL_ShowCursor(1);

    inicializar_botones();

    //setteo "default" de valores
    // set_fondo(fondos_img[0]);
    // set_tile(tiles_img[0]);

    bool correr_programa = true;
    SDL_Event event;

    while (correr_programa) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                correr_programa = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                
                if (!tile_actual.empty()) {
                    // Assuming each tile is 32x32 pixels (adjust accordingly)
                    int tile_x = x / 32; // Calculate the grid position
                    int tile_y = y / 32;

                    // Store the tile placement
                    if (tiles_seleccionados.count(tile_actual) > 0){ //nos permite buscar si ya pusimos tiles
                                                                     //con esta textura

                        tiles_seleccionados[tile_actual].push_back({tile_x, tile_y});
                        
                    } else {
                        std::vector<SDL_Point> tiles;
                        tiles.push_back({tile_x, tile_y});
                        tiles_seleccionados[tile_actual] = tiles;
                    }
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
                if (!tile_actual.empty()) {
                    tile_actual.clear();
                }
            }

            boton_fondo.evento_click(event, [&]() {
                mostrar_opciones_fondo();
            });

            boton_tiles.evento_click(event, [&]() {
                mostrar_opciones_tiles();
            });


        if (mostrar_fondos_disponibles) {
            for (size_t i = 0; i < fondos_posibles_boton.size(); ++i) {
                fondos_posibles_boton[i].evento_click(event, [this, i]() {
                    actualizar_fondo(i); 
                });
            }
        }

        if (mostrar_tiles_disponibles) {
            for (size_t i = 0; i < tiles_posibles_boton.size(); ++i) {
                tiles_posibles_boton[i].evento_click(event, [this, i]() {
                    actualizar_tiles(i); 
                });
            }
        }
        }
        limpiar_pantalla();


        renderer.SetDrawColor(0, 0, 0, 255);
        renderizar_fondo();
        renderizar_tiles();

        boton_fondo.render(renderer);
        boton_tiles.render(renderer);

       
        if (mostrar_fondos_disponibles) {
            for (auto& boton_opcion : fondos_posibles_boton) {
                boton_opcion.render(renderer);
            }
        }

        if (mostrar_tiles_disponibles) {
            for (auto& boton_opcion : tiles_posibles_boton) {
                boton_opcion.render(renderer);
            }
        }
        
        
        renderer.Present();
    }

    // loadTiles();

    // initEntities();

    // initMap();
    
    //inicializar pantalla en blanco
    //renderer.SetDrawColor(255, 255, 255, 255);

    // agregar_entidades();

    // 

    SDL_Quit();
    IMG_Quit();
    
}

void Editor::set_fondo(std::string path_fondo) {
    fondo_actual = path_fondo;
}

void Editor::inicializar_botones() {
    for (size_t i = 0; i < fondos_img.size(); ++i) {
        fondos_posibles_boton.emplace_back(10, 70 + i * 60, 180, 50, fondos_img[i]);
    }

    for (size_t i = 0; i < tiles_img.size(); ++i) {
        tiles_posibles_boton.emplace_back(200, 70 + i * 60, 180, 50, tiles_img[i]);
    }
}

void Editor::mostrar_opciones_fondo() {
    mostrar_fondos_disponibles = !mostrar_fondos_disponibles;
}

void Editor::mostrar_opciones_tiles() {
    mostrar_tiles_disponibles = !mostrar_tiles_disponibles;
}

void Editor::actualizar_fondo(int indice) {
    set_fondo(fondos_img[indice]);
    renderizar_fondo();
   
}

void Editor::actualizar_tiles(int indice) {
    set_tile(fondos_img[indice]);
    renderizar_tiles();
}

void Editor::limpiar_pantalla() {
    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.Clear();
}

void Editor::renderizar_fondo(){
    if (fondo_actual.empty()){
        return;
    }
    SDL2pp::Surface surface(IMG_Load(fondo_actual.c_str()));
    SDL2pp::Texture textura(renderer, surface);
    renderer.Copy(textura, SDL2pp::Optional<SDL2pp::Rect>(),
                  SDL2pp::Optional<SDL2pp::Rect>());
}

void Editor::set_tile(std::string path_tile) {
    tile_actual = path_tile;
}

void Editor::renderizar_tiles() {
    if (tiles_seleccionados.empty()){
        return;
    }
    for (const auto& textura_punto : tiles_seleccionados) {
        // Draw each tile at its position
        // Recordar que estamos cargando la imagen constantemente, no tiene sentido!.
        SDL2pp::Surface surface(IMG_Load(textura_punto.first.c_str()));
        SDL2pp::Texture textura(renderer, surface);
        
        std::vector<SDL_Point> puntos = textura_punto.second;

        for (const auto& punto : puntos){
            renderer.Copy(textura, SDL2pp::Optional<SDL2pp::Rect>(),
                      SDL2pp::Rect(punto.x * 32, punto.y * 32, 32, 32));
        }
    }
}


// void drawGridLines(int spacing, SDL2pp::Renderer& renderer)
// {
//     int x, y;

//     renderer.SetDrawColor(255, 255, 255, 255);

//     for (x = 0; x < SCREEN_WIDTH; x += spacing)
//     {
//         renderer.DrawLine(x, 0, x, SCREEN_HEIGHT);
//     }

//     for (y = 0; y < SCREEN_WIDTH; y += spacing)
//     {
//         renderer.DrawLine(0, y, SCREEN_WIDTH, y);
//     }
//     renderer.Present();
// }



