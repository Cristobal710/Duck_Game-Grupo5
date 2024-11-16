#include "editor.h"
#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280
#define ARMADURA "../resources/armors/chestPlatePickup.png"
#define ARMA "../resources/weapons/ak47.png"
#define CASCO "../resources/armors/knightHelmet.png"
#define SIZE_ARMA 32
#define SIZE_ARMADURAS 16


Editor::Editor(): window("Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE),
                  renderer(window, -1, SDL_RENDERER_ACCELERATED),   

mostrar_fondos_disponibles(false), mostrar_tiles_disponibles(false),
mostrar_spawns_disponibles(false),
mostrar_equipamiento_disponibles(false), mostrar_cajas_disponibles(false),
font(TTF_OpenFont("../resources/fonts/Open_Sans/static/OpenSans-Italic.ttf", 12)),
boton_fondo(10, 10, 180, 50, "Elegir Fondo", font),
boton_tiles(200, 10, 180, 50, "Elegir Tiles", font),
boton_spawn(390, 10, 180, 50, "Spawns de patos", font),
boton_equipamiento(580, 10, 180, 50, "Equipamiento", font),
boton_cajas(770, 10, 180, 50, "cajas", font),
tiles_seleccionados(), spawn_seleccionados(), equipamiento_seleccionados(), cajas_seleccionados() 
    {}


void Editor::iniciar_editor() {
    
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_ShowCursor(1);
    inicializar_botones();

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
                    // tamano de los tiles, 32x32 por ahora
                    int tile_x = x / 16; 
                    int tile_y = y / 16;

                    
                    if (tiles_seleccionados.count(tile_actual) > 0){ //nos permite buscar si ya pusimos tiles
                                                                     //con esta textura

                        tiles_seleccionados[tile_actual].push_back({tile_x, tile_y});
                        
                    } else {
                        std::vector<SDL_Point> tiles;
                        tiles.push_back({tile_x, tile_y});
                        tiles_seleccionados[tile_actual] = tiles;
                    }
                }

                if (!spawn_actual.empty()) {
                    // tamano de los spawns, 32x32 por ahora
                    int tile_x = x / 32; 
                    int tile_y = y / 32;

                    
                    if (spawn_seleccionados.count(spawn_actual) > 0){ //nos permite buscar si ya pusimos tiles
                                                                     //con esta textura

                        spawn_seleccionados[spawn_actual].push_back({tile_x, tile_y});
                        
                    } else {
                        std::vector<SDL_Point> spawns;
                        spawns.push_back({tile_x, tile_y});
                        spawn_seleccionados[spawn_actual] = spawns;
                    }
                }

                if (!equipamiento_actual.empty()) {
                    int tile_x; 
                    int tile_y;
                    if (equipamiento_actual == ARMA){
                        tile_x = x / 32; 
                        tile_y = y / 32;
                    } else {
                        tile_x = x / 16; 
                        tile_y = y / 16;
                    }

                    
                    if (equipamiento_seleccionados.count(equipamiento_actual) > 0){ //nos permite buscar si ya pusimos tiles
                                                                     //con esta textura

                        equipamiento_seleccionados[equipamiento_actual].push_back({tile_x, tile_y});
                        
                    } else {
                        std::vector<SDL_Point> equipamiento;
                        equipamiento.push_back({tile_x, tile_y});
                        equipamiento_seleccionados[equipamiento_actual] = equipamiento;
                    }
                }

                if (!caja_actual.empty()) {
                    // tamano de los spawns, 32x32 por ahora
                    int tile_x = x / 32; 
                    int tile_y = y / 32;

                    
                    if (cajas_seleccionados.count(caja_actual) > 0){ //nos permite buscar si ya pusimos tiles
                                                                     //con esta textura
                        cajas_seleccionados[caja_actual].push_back({tile_x, tile_y});
                        
                    } else {
                        std::vector<SDL_Point> caja;
                        caja.push_back({tile_x, tile_y});
                        cajas_seleccionados[caja_actual] = caja;
                    }
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
                if (!tile_actual.empty()) {
                    tile_actual.clear();
                    mostrar_tiles_disponibles = false;
                }
                if (!spawn_actual.empty()) {
                    spawn_actual.clear();
                    mostrar_spawns_disponibles = false;
                }
                if (!equipamiento_actual.empty()){
                    equipamiento_actual.clear();
                    mostrar_equipamiento_disponibles = false;
                }
                if (!caja_actual.empty()){
                    caja_actual.clear();
                    mostrar_cajas_disponibles = false;
                }
            }

            boton_fondo.evento_click(event, [&]() {
                mostrar_opciones_fondo();
            });

            boton_tiles.evento_click(event, [&]() {
                mostrar_opciones_tiles();
            });

            boton_spawn.evento_click(event, [&]() {
                mostrar_opciones_spawn();
            });

            boton_equipamiento.evento_click(event, [&](){
                mostrar_opciones_equipamiento();
            });

            boton_cajas.evento_click(event, [&](){
                mostrar_opciones_cajas();
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

        if (mostrar_spawns_disponibles) {
            for (size_t i = 0; i < spawns_disponibles_boton.size(); ++i) {
                spawns_disponibles_boton[i].evento_click(event, [this, i]() {
                    actualizar_spawn(i); 
                });
            }
        }
        if (mostrar_equipamiento_disponibles){
            for (size_t i = 0; i < equipamiento_disponibles_boton.size(); ++i) {
                equipamiento_disponibles_boton[i].evento_click(event, [this, i]() {
                    actualizar_equipamiento(i); 
                });
            }
        }

        if (mostrar_cajas_disponibles){
            for (size_t i = 0; i < cajas_disponibles_boton.size(); ++i) {
                cajas_disponibles_boton[i].evento_click(event, [this, i]() {
                    actualizar_cajas(i); 
                });
            }
        }

        }
        limpiar_pantalla();


        renderer.SetDrawColor(0, 0, 0, 255);
        renderizar_fondo();
        renderizar_tiles();
        renderizar_spawn();
        renderizar_equipamiento();
        renderizar_caja();

        boton_fondo.render(renderer);
        boton_tiles.render(renderer);
        boton_spawn.render(renderer);
        boton_equipamiento.render(renderer);
        boton_cajas.render(renderer);

       
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

        if (mostrar_spawns_disponibles) {
            for (auto& boton_opcion : spawns_disponibles_boton) {
                boton_opcion.render(renderer);
            }
        }

        if (mostrar_equipamiento_disponibles){
            for (auto& boton_opcion : equipamiento_disponibles_boton) {
                boton_opcion.render(renderer);
            }
        }

        if (mostrar_cajas_disponibles){
            for (auto& boton_opcion : cajas_disponibles_boton) {
                boton_opcion.render(renderer);
            }
        }
        
        
        renderer.Present();
    }

    // loadTiles();

    // initEntities();

    // initMap();
    //cerrar_botones();

    SDL_Quit();
    IMG_Quit();
    //TTF_Quit();

    std::cout << "Ingresar nombre del archivo para guardarlo o apriete ENTER para cerrar el programa: " << std::endl;

    std::string nombre_archivo;
    std::getline(std::cin, nombre_archivo);
    if (nombre_archivo.empty()){
        return;
    }
    guardar_mapa(nombre_archivo);
    renderer.~Renderer();
}

void Editor::set_fondo(std::string path_fondo) {
    fondo_actual = path_fondo;
}

void Editor::inicializar_botones() {
    for (size_t i = 0; i < fondos_img.size(); ++i) {
        fondos_posibles_boton.emplace_back(10, 70 + i * 60, 180, 50, nombre_entidad(fondos_img[i]), font);
    }

    for (size_t i = 0; i < tiles_img.size(); ++i) {
        tiles_posibles_boton.emplace_back(200, 70 + i * 60, 180, 50, nombre_entidad(tiles_img[i]) , font);
    }

    for (size_t i = 0; i < spawn_img.size(); ++i) {
        spawns_disponibles_boton.emplace_back(390, 70 + i * 60, 180, 50, nombre_entidad(spawn_img[i]), font);
    }

    for (size_t i = 0; i < equipamiento_img.size(); ++i) {
        equipamiento_disponibles_boton.emplace_back(580, 70 + i * 60, 180, 50, nombre_entidad(equipamiento_img[i]), font);
    }

    for (size_t i = 0; i < cajas_img.size(); ++i) {
        cajas_disponibles_boton.emplace_back(770, 70 + i * 60, 180, 50, nombre_entidad(cajas_img[i]), font);
    }
}

void Editor::mostrar_opciones_fondo() {
    mostrar_fondos_disponibles = !mostrar_fondos_disponibles;
}

void Editor::mostrar_opciones_tiles() {
    mostrar_tiles_disponibles = !mostrar_tiles_disponibles;
}

void Editor::mostrar_opciones_spawn() {
    mostrar_spawns_disponibles = !mostrar_spawns_disponibles;
}

void Editor::mostrar_opciones_equipamiento() {
    mostrar_equipamiento_disponibles = !mostrar_equipamiento_disponibles;
}

void Editor::mostrar_opciones_cajas() {
    mostrar_cajas_disponibles = !mostrar_cajas_disponibles;
}


void Editor::actualizar_fondo(int indice) {
    set_fondo(fondos_img[indice]);
    renderizar_fondo();
   
}

void Editor::actualizar_tiles(int indice) {
    set_tile(tiles_img[indice]);
    renderizar_tiles();
}

void Editor::actualizar_spawn(int indice) {
    set_spawn(spawn_img[indice]);
    renderizar_tiles();
}

void Editor::actualizar_equipamiento(int indice) {
    set_equipamiento(equipamiento_img[indice]);
    renderizar_equipamiento();
}

void Editor::actualizar_cajas(int indice) {
    set_caja(cajas_img[indice]);
    renderizar_caja();
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
        // Recordar que estamos cargando la imagen constantemente, no tiene sentido!.
        SDL2pp::Surface surface(IMG_Load(textura_punto.first.c_str()));
        SDL2pp::Texture textura(renderer, surface);
        
        std::vector<SDL_Point> puntos = textura_punto.second;

        for (const auto& punto : puntos){
            renderer.Copy(textura, SDL2pp::Optional<SDL2pp::Rect>(),
                      SDL2pp::Rect(punto.x * 16, punto.y * 16, 16, 16));
        }
    }
}

void Editor::set_spawn(std::string path_spawn) {
    spawn_actual = path_spawn;
}

void Editor::renderizar_spawn() {
    if (spawn_seleccionados.empty()){
        return;
    }
    for (const auto& textura_punto : spawn_seleccionados) {
        // Recordar que estamos cargando la imagen constantemente, no tiene sentido!.
        SDL2pp::Surface surface(IMG_Load(textura_punto.first.c_str()));

        SDL_Rect rect_inicial = {1, 7, 32, 32};

        SDL2pp::Surface sprite_superficie(
                SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0));

        SDL_BlitSurface(surface.Get(), &rect_inicial, sprite_superficie.Get(), nullptr);

        Uint32 color_key = SDL_MapRGB(sprite_superficie.Get()->format, 0, 0, 0);

        SDL_SetColorKey(sprite_superficie.Get(), SDL_TRUE, color_key);

        SDL2pp::Texture textura(renderer, sprite_superficie);


        //SDL2pp::Texture textura(renderer, surface);
        
        std::vector<SDL_Point> puntos = textura_punto.second;

        for (const auto& punto : puntos){
            renderer.Copy(textura, SDL2pp::Optional<SDL2pp::Rect>(),
                      SDL2pp::Rect(punto.x * 32, punto.y * 32, 32, 32));
        }
    }
}

void Editor::set_equipamiento(std::string path_equipamiento) {
    equipamiento_actual = path_equipamiento;
}

void Editor::renderizar_equipamiento() {
    if (equipamiento_seleccionados.empty()){
        return;
    }
    
    for (const auto& textura_punto : equipamiento_seleccionados) {

        int tile_size; 
        if (textura_punto.first == ARMA){
            tile_size = SIZE_ARMA; 
        } else {
            tile_size = SIZE_ARMADURAS; 
        }
        // Recordar que estamos cargando la imagen constantemente, no tiene sentido!.
        SDL2pp::Surface surface(IMG_Load(textura_punto.first.c_str()));


        SDL_Rect rect_inicial = {1, 7, tile_size, tile_size};

        SDL2pp::Surface sprite_superficie(
                SDL_CreateRGBSurface(0, tile_size, tile_size, tile_size, 0, 0, 0, 0));

        SDL_BlitSurface(surface.Get(), &rect_inicial, sprite_superficie.Get(), nullptr);

        Uint32 color_key = SDL_MapRGB(sprite_superficie.Get()->format, 0, 0, 0);

        SDL_SetColorKey(sprite_superficie.Get(), SDL_TRUE, color_key);

        SDL2pp::Texture textura(renderer, sprite_superficie);
        
        std::vector<SDL_Point> puntos = textura_punto.second;

        for (const auto& punto : puntos){
            renderer.Copy(textura, SDL2pp::Optional<SDL2pp::Rect>(),
                      SDL2pp::Rect(punto.x * tile_size, punto.y * tile_size, tile_size, tile_size));
        }
    }
}

void Editor::set_caja(std::string path_caja) {
    caja_actual = path_caja;
}

void Editor::renderizar_caja() {
    if (cajas_seleccionados.empty()){
        return;
    }
    for (const auto& textura_punto : cajas_seleccionados) {
        // Recordar que estamos cargando la imagen constantemente, no tiene sentido!.
        SDL2pp::Surface surface(IMG_Load(textura_punto.first.c_str()));

        SDL_Rect rect_inicial = {1, 7, 32, 32};

        SDL2pp::Surface sprite_superficie(
                SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0));

        SDL_BlitSurface(surface.Get(), &rect_inicial, sprite_superficie.Get(), nullptr);

        Uint32 color_key = SDL_MapRGB(sprite_superficie.Get()->format, 0, 0, 0);

        SDL_SetColorKey(sprite_superficie.Get(), SDL_TRUE, color_key);

        SDL2pp::Texture textura(renderer, sprite_superficie);
        
        std::vector<SDL_Point> puntos = textura_punto.second;

        for (const auto& punto : puntos){
            renderer.Copy(textura, SDL2pp::Optional<SDL2pp::Rect>(),
                      SDL2pp::Rect(punto.x * 32, punto.y * 32, 32, 32));
        }
    }
}

void Editor::guardar_mapa(std::string& nombre_archivo) {
    json json_mapa;

    if (!fondo_actual.empty()){
        json_mapa["background"] = fondo_actual;
    }
    if (!tiles_seleccionados.empty()){
        for (const auto& tiles : tiles_seleccionados) {
        std::vector<SDL_Point> puntos = tiles.second;

        for (const auto& punto : puntos){
                json json_tiles;
                json_tiles["texture"] = tiles.first;
                json_tiles["x"] = (punto.x) * 16;
                json_tiles["y"] = (punto.y) * 16;
                json_mapa["tiles"].push_back(json_tiles);
            }
        }
    }
    
    if (!spawn_seleccionados.empty()){
        for (const auto& spawns : spawn_seleccionados) {
        std::vector<SDL_Point> puntos = spawns.second;

        for (const auto& punto : puntos){
                json json_spawns;
                json_spawns["x"] = (punto.x) * 32;
                json_spawns["y"] = (punto.y) * 32;
                json_mapa["spawns"].push_back(json_spawns);
            }
        }
    }
    
    if (!equipamiento_seleccionados.empty()){
        for (const auto& equipamiento : equipamiento_seleccionados) {
        std::vector<SDL_Point> puntos = equipamiento.second;

        for (const auto& punto : puntos){
                json json_equipment;
                if (equipamiento.first == ARMADURA){
                    json_equipment["armadura"] = equipamiento.first;
                    json_equipment["x"] = (punto.x) * 16;
                    json_equipment["y"] = (punto.y) * 16;
                    json_mapa["equipamiento"].push_back(json_equipment);
                } else if (equipamiento.first == ARMA){
                    json_equipment["arma"] = equipamiento.first;
                    json_equipment["x"] = (punto.x) * 32;
                    json_equipment["y"] = (punto.y) * 32;
                    json_mapa["equipamiento"].push_back(json_equipment);
                } else {
                    json_equipment["casco"] = equipamiento.first;
                    json_equipment["x"] = (punto.x) * 16;
                    json_equipment["y"] = (punto.y) * 16;
                    json_mapa["equipamiento"].push_back(json_equipment);
                }

                
            }
        }
    }

    if (!cajas_seleccionados.empty()){
        for (const auto& cajas : cajas_seleccionados) {
        std::vector<SDL_Point> puntos = cajas.second;

        for (const auto& punto : puntos){
                json json_cajas;
                json_cajas["x"] = (punto.x) * 32;
                json_cajas["y"] = (punto.y) * 32;
                json_mapa["spawns"].push_back(json_cajas);
            }
        }
    }

    std::string file_nombre = "../resources/maps/" + nombre_archivo;

    std::ofstream file_final(file_nombre);

    if (file_final.is_open()) {
        
        file_final << json_mapa.dump(4); 

        file_final.close();
        std::cout << "Mapa guardado correctamente en: " << file_nombre << std::endl;
    } else {
        std::cerr << "No pudo abrirse el archivo " << file_nombre << std::endl;
    }
}

std::string Editor::nombre_entidad(const std::string& path) { 
    
    size_t lastSlash = path.find_last_of("/\\");
   
    std::string filename = (lastSlash == std::string::npos) ? path : path.substr(lastSlash + 1);
    
    size_t dotPos = filename.find_last_of('.');
    if (dotPos != std::string::npos) {
        filename = filename.substr(0, dotPos);
    }
    return filename;
 }
