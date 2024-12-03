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
#define PATH_SPAWN "../resources/Grey-Duck.png"
#define PATH_CAJA  "../resources/TileSets/uiBox.png"

using json = nlohmann::json;

class Editor {
    private:
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    
    bool mostrar_fondos_disponibles;
    bool mostrar_tiles_disponibles;
    bool mostrar_spawns_disponibles;
    bool mostrar_equipamiento_disponibles;
    bool mostrar_cajas_disponibles;
    bool mostrar_mapas_disponibles;

    TTF_Font* font;

    Button boton_fondo;
    Button boton_tiles;
    Button boton_spawn;
    Button boton_equipamiento;
    Button boton_cajas;
    Button boton_mapas;

    std::map<std::string,std::vector<SDL_Point>>  tiles_seleccionados;  
    std::map<std::string,std::vector<SDL_Point>>  spawn_seleccionados;
    std::map<std::string,std::vector<SDL_Point>>  equipamiento_seleccionados;
    std::map<std::string,std::vector<SDL_Point>>  cajas_seleccionados;

    std::vector<Button> fondos_posibles_boton;
    std::vector<Button> tiles_posibles_boton;
    std::vector<Button> spawns_disponibles_boton;
    std::vector<Button> equipamiento_disponibles_boton;
    std::vector<Button> cajas_disponibles_boton;
    std::vector<Button> mapas_disponibles_boton;

   

    std::string fondo_actual;
    std::string tile_actual;
    std::string spawn_actual;
    std::string equipamiento_actual;
    std::string caja_actual;


    

    std::vector<std::string> fondos_img = {
        "../resources/backgrounds/city.png",
        "../resources/backgrounds/forest.png",
        "../resources/backgrounds/city_bg.png"
        //se pueden agregar mas fondos aca
    };
    std::vector<std::string> tiles_img = {
        "../resources/TileSets/Tileset_Fantasy.png",
        "../resources/TileSets/greyBlock.png",
        "../resources/TileSets/brownTile.png"
    };

    std::vector<std::string> spawn_img = {
        "../resources/Grey-Duck.png",
    };

    std::vector<std::string> equipamiento_img = {
        "../resources/armors/knightHelmet.png",
        "../resources/weapons/ak47.png",
        "../resources/armors/chestPlatePickup.png",
    };

    std::vector<std::string> cajas_img = {
        "../resources/boxes/Box_.png",
    };

    std::vector<std::string> mapas = {
        "../resources/maps/mapa3",
        "../resources/maps/mapa5",
        "../resources/maps/mapa4",
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
    void set_equipamiento(std::string path_equipamiento);
    void renderizar_equipamiento();
    void set_caja(std::string path_caja);
    void renderizar_caja();
    
    void mostrar_opciones_fondo();
    void mostrar_opciones_tiles();
    void mostrar_opciones_spawn();
    void mostrar_opciones_equipamiento();
    void mostrar_opciones_cajas();
    void mostrar_opciones_mapas();

    void actualizar_fondo(int indice);
    void actualizar_tiles(int indice);
    void actualizar_spawn(int indice);
    void actualizar_equipamiento(int indice);
    void actualizar_cajas(int indice);
    void elegir_mapa(int indice);
    
    void procesar_mapa(json& j);

    void limpiar_pantalla();
    void guardar_mapa(std::string& nombre_archivo);

    std::string nombre_entidad(const std::string& path);
}
;


#endif
