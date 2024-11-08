#ifndef EDITOR_H
#define EDITOR_H
#include <vector>
#include "button.h"
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <SDL2pp/SDL2pp.hh>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Editor {
    private:
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    
    bool mostrar_fondos_disponibles;
    bool mostrar_tiles_disponibles;
    bool mostrar_spawns_disponibles;

    TTF_Font* font;

    Button boton_fondo;
    Button boton_tiles;
    Button boton_spawn;

    std::map<std::string,std::vector<SDL_Point>>  tiles_seleccionados;  
    std::map<std::string,std::vector<SDL_Point>>  spawn_seleccionados;

    std::vector<Button> fondos_posibles_boton;
    std::vector<Button> tiles_posibles_boton;
    std::vector<Button> spawns_disponibles_boton;

   

    std::string fondo_actual;
    std::string tile_actual;
    std::string spawn_actual;


    

    std::vector<std::string> fondos_img = {
        "../resources/backgrounds/city.png",
        "../resources/backgrounds/forest.png",
        "../resources/backgrounds/city_bg.png"
        //se pueden agregar mas fondos aca
    };
    std::vector<std::string> tiles_img = {
        "../resources/TileSets/Tileset_Fantasy.png",
        "../resources/TileSets/greyBlock.png"
    };

    std::vector<std::string> spawn_img = {
        "../resources/Grey-Duck.png",
    };

    

    public:
    Editor();
    void iniciar_editor();
    void inicializar_botones();
    
    void set_fondo(std::string path_fondo);
    void renderizar_fondo();
    void set_tile(std::string path_tile);
    void renderizar_tiles();
    void set_spawn(std::string path_spawn);
    void renderizar_spawn();
    
    void mostrar_opciones_fondo();
    void mostrar_opciones_tiles();
    void mostrar_opciones_spawn();
    

    void actualizar_fondo(int indice);
    void actualizar_tiles(int indice);
    void actualizar_spawn(int indice);
    
    void limpiar_pantalla();
    void guardar_mapa(std::string& nombre_archivo);

    std::string nombre_entidad(const std::string& path);
}
;


#endif
