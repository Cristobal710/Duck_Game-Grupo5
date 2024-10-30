#ifndef EDITOR_H
#define EDITOR_H
#include <vector>
#include "button.h"
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

class Editor {
    private:
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;

    Button boton_fondo;
    Button boton_tiles;
    
    bool mostrar_fondos_disponibles;
    bool mostrar_tiles_disponibles;

    std::map<std::string,std::vector<SDL_Point>>  tiles_seleccionados;  

    std::vector<Button> fondos_posibles_boton;
    std::vector<Button> tiles_posibles_boton;

   

    std::string fondo_actual;
    std::string tile_actual;


    

    std::vector<std::string> fondos_img = {
        "../resources/backgrounds/city.png",
        "../resources/backgrounds/forest.png",
        "../resources/backgrounds/city_bg.png"
        //se pueden agregar mas fondos aca
    };
    std::vector<std::string> tiles_img = {
        "../resources/TileSets/Tileset_Fantasy.png",
        
    };

    

    public:
    Editor();
    void iniciar_editor();
    void inicializar_botones();
    
    void set_fondo(std::string path_fondo);
    void renderizar_fondo();
    void set_tile(std::string path_tile);
    void renderizar_tiles();
    
    void mostrar_opciones_fondo();
    void mostrar_opciones_tiles();
    

    void actualizar_fondo(int indice);
    void actualizar_tiles(int indice);
    
    void limpiar_pantalla();
    

}
;


#endif
