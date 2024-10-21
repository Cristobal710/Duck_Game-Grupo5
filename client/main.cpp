#include <iostream>
#include <exception>
#include <vector>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define NUM_FRAMES_MOVIMIENTO_PATO 6
#define PIXEL_PATO 32

using namespace SDL2pp;


// Function to load multiple sprites into a vector
void frames_movimientos(SDL2pp::Renderer& renderer, SDL2pp::Surface& spriteSheet,
int frameWidth, int frameHeight, std::vector<SDL2pp::Texture>& textures) {
    
    for (int i = 0; i < NUM_FRAMES_MOVIMIENTO_PATO; ++i) {

        SDL_Rect srcRect = {i * frameWidth, 6, frameWidth, frameHeight}; 
        
        SDL2pp::Surface spriteSurface(SDL_CreateRGBSurface(0, frameWidth, frameHeight, 32, 0, 0, 0, 0));
        
        SDL_BlitSurface(spriteSheet.Get(), &srcRect, spriteSurface.Get(), nullptr);
        
        SDL2pp::Texture spriteTexture(renderer, spriteSurface);
        
        textures.emplace_back(std::move(spriteTexture)); 
    }
}


void pato_camina_derecha(std::vector<SDL2pp::Texture>& movimiento_pato, SDL2pp::Renderer& renderer,
                        SDL_Rect& src_rect,SDL2pp::Rect& dst_rect) {
    
    for (int i = 0; i < NUM_FRAMES_MOVIMIENTO_PATO; ++i){
        
        dst_rect.x += 2 ;
        renderer.Copy(movimiento_pato[i], SDL2pp::Optional<SDL2pp::Rect>(src_rect), SDL2pp::Optional<SDL2pp::Rect>(dst_rect));
        renderer.Present();


        SDL_Delay(100); 
    }

    renderer.Copy(movimiento_pato[0], SDL2pp::Optional<SDL2pp::Rect>(src_rect), SDL2pp::Optional<SDL2pp::Rect>(dst_rect));
    
    renderer.Present();
    
}

void pato_camina_izquierda(std::vector<SDL2pp::Texture>& movimiento_pato, SDL2pp::Renderer& renderer,
SDL_Rect& src_rect,SDL2pp::Rect& dst_rect ) {
    
    for (int i = 0; i < NUM_FRAMES_MOVIMIENTO_PATO; ++i){
        renderer.Copy(movimiento_pato[0], SDL2pp::Optional<SDL2pp::Rect>(src_rect), SDL2pp::Optional<SDL2pp::Rect>(dst_rect));
        dst_rect.x -= 2 ; //aca no sabemos cuanto nos tenemos que mover realmente, es arbitrario el valor ahora mismo

        SDL_RenderCopyEx(renderer.Get(), movimiento_pato[i].Get(), &src_rect, &dst_rect, 0, nullptr, SDL_FLIP_HORIZONTAL);

        renderer.Present();


        SDL_Delay(85); 
    }

    SDL_RenderCopyEx(renderer.Get(), movimiento_pato[0].Get(), &src_rect, &dst_rect, 0, nullptr, SDL_FLIP_HORIZONTAL);

    renderer.Present();
    
}


int main() {    
    // inicializar el SDL video, lo requiere el SDL_PollEvent en la documentacion.
    // As this function may implicitly call SDL_PumpEvents(), you can only call
    // this function in the thread that initialized the video subsystem.


    std::vector<SDL2pp::Texture> movimiento_pato;

	SDL sdl(SDL_INIT_VIDEO);

    // Initialize SDL_image
        IMG_Init(IMG_INIT_PNG);

        // Create main window
        SDL2pp::Window window("SDL2 Image Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_RESIZABLE);
        
        // Create renderer
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL2pp::Surface sprite_pato_gris(IMG_Load("../resources/Grey-Duck.png"));
        
        //lugar de inicio del pato
        SDL2pp::Rect src_rect = {1, 8, 32, 32};

        //conseguir sprites de movimiento
        frames_movimientos(renderer, sprite_pato_gris, PIXEL_PATO, PIXEL_PATO, movimiento_pato);

        // Clear screen
        renderer.Clear();

        // Define the destination rectangle where the sprite will be drawn
        SDL2pp::Rect dst_rect = {100, 100, 32, 32}; // Position at (100, 100)

        // Copy the sprite texture to the renderer, specifying the destination rectangle
        renderer.Copy(movimiento_pato[0], src_rect, dst_rect);

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
                if (evento.key.keysym.sym == SDLK_d) {
                    //aca vendria la logica de moverte para la derecha.
                    renderer.Clear();
                    pato_camina_derecha(movimiento_pato, renderer, src_rect, dst_rect);   
                    continue;
                }
                if (evento.key.keysym.sym == SDLK_a) {
                    //aca vendria la logica de moverte para la izqueirda.
                    renderer.Clear();
                    pato_camina_izquierda(movimiento_pato, renderer, src_rect, dst_rect);   
                    continue;
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


