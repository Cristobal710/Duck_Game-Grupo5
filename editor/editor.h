#ifndef EDITOR_H
#define EDITOR_H
#include <vector>
#include "button.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

class Editor {
    private:
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;

    Button boton_fondo;
    std::vector<Button> fondos_posibles_boton;
    bool mostrar_fondos_disponibles = false;
    std::string fondo_actual;
    std::vector<std::string> fondos_img = {
        "../resources/city.png",
        "../resources/forest.png",
        "../resources/city_bg.png"
        //se pueden agregar mas fondos aca
    };

    

    public:
    Editor();
    void iniciar_editor();
    void set_fondo(std::string path_fondo);
    void renderizar_fondo();
    void mostrar_opciones_fondo();
    void inicializar_botones();
    void actualizar_fondo(int index);
    void limpiar_pantalla();
    

}
;


#endif
