#include "editor.h"
#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280

Editor::Editor(): window("Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE),
                  renderer(window, -1, SDL_RENDERER_ACCELERATED),   
boton_fondo(10, 10, 200, 50, "Elegir Fondo") 
{}


void Editor::iniciar_editor() {
    
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    
    SDL_ShowCursor(1);

    inicializar_botones();

    //setteo "default" de valores
    set_fondo("../resources/city.png");

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            boton_fondo.evento_click(event, [&]() {
                mostrar_opciones_fondo();
            });

        if (mostrar_fondos_disponibles) {
            for (size_t i = 0; i < fondos_posibles_boton.size(); ++i) {
                fondos_posibles_boton[i].evento_click(event, [this, i]() {
                    actualizar_fondo(i); 
                });
            }
        }
        }
        limpiar_pantalla();


        renderer.SetDrawColor(0, 0, 0, 255);
        renderizar_fondo();

        boton_fondo.render(renderer);

       
        if (mostrar_fondos_disponibles) {
            for (auto& boton_opcion : fondos_posibles_boton) {
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
        fondos_posibles_boton.emplace_back(10, 70 + i * 60, 200, 50, fondos_img[i]);
    }
}

void Editor::mostrar_opciones_fondo() {
    mostrar_fondos_disponibles = !mostrar_fondos_disponibles;
}

void Editor::actualizar_fondo(int index) {
    set_fondo(fondos_img[index]);
    renderizar_fondo();
   
}

void Editor::limpiar_pantalla() {
    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.Clear();
}

void Editor::renderizar_fondo(){
    limpiar_pantalla();
    SDL2pp::Surface surface(IMG_Load(fondo_actual.c_str()));
    SDL2pp::Texture textura(renderer, surface);
    renderer.Copy(textura, SDL2pp::Optional<SDL2pp::Rect>(),
                  SDL2pp::Optional<SDL2pp::Rect>());
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



