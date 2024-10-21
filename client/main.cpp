#include <iostream>
#include <exception>
#include <vector>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace SDL2pp;

int main() {    
    // inicializar el SDL video, lo requiere el SDL_PollEvent en la documentacion.
    // As this function may implicitly call SDL_PumpEvents(), you can only call
    // this function in the thread that initialized the video subsystem.

	SDL sdl(SDL_INIT_VIDEO);

    // Initialize SDL_image
        IMG_Init(IMG_INIT_PNG);

        // Create main window
        SDL2pp::Window window("SDL2 Image Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
        
        // Create renderer
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL2pp::Surface sprite_pato_gris(IMG_Load("../src/Grey-Duck.png"));
        

        // Create texture from surface using SDL2pp::Texture
        SDL2pp::Texture texture(renderer, sprite_pato_gris);

        // Clear screen
        renderer.Clear();

        // Copy texture to renderer
        renderer.Copy(texture);

        // Show rendered frame
        renderer.Present();
    //Terminado del preparado de las ventanas
    
    //main loop del cliente
    SDL_Event evento;
    bool correr_programa = true;

    while (correr_programa){

       
        while (SDL_PollEvent(&evento)){

            //chequeamos si se clickeo el boton de Exit
            if (evento.type == SDL_QUIT){
            correr_programa = false;
            }

            //apretar ESC equivale a cerrar el programa aca
            else if (evento.type == SDL_KEYDOWN) {
                if (evento.key.keysym.sym == SDLK_ESCAPE) {
                    correr_programa = false; 
                }
            }
        }

        //una vez salido de procesar todos los eventos de nuestro jugador
        //hay que implementar los siguientes metodos.
        //actualizar_estado_juego();
        //limpiar_display();??? -> es simplemente un clear de toda la pantalla?
        //actualizar_animacion(it?);
        //renderizar_en_orden_z();
        //it = dormir_y_calcular_prox_iteracion(FPS, x);
    }
    IMG_Quit();
    return 0;
}


