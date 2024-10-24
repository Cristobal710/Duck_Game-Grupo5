#include <iostream>
#include <exception>
#include <vector>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define NUM_FRAMES_MOVIMIENTO_PATO 6
#define NUM_FRAMES_SALTA_PATO 3
#define NUM_FRAMES_BAJA_PATO 6
#define NUM_FRAMES_PATO_ACOSTADO 5
#define PIXEL_PATO 32

using namespace SDL2pp;



void frames_movimientos(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
int frame_width, int frame_height, std::vector<SDL2pp::Texture>& texturas) {
    
    for (int i = 0; i < NUM_FRAMES_MOVIMIENTO_PATO; ++i) {

        SDL_Rect rect_inicial = {i * frame_width, 6, frame_width, frame_height}; 
        
        SDL2pp::Surface sprite_superficie(SDL_CreateRGBSurface(0, frame_width, frame_height, 32, 0, 0, 0, 0));
        


        SDL_BlitSurface(sprite_sheet.Get(), &rect_inicial, sprite_superficie.Get(), nullptr);
        
        Uint32 color_key = SDL_MapRGB(sprite_superficie.Get()->format, 0, 0, 0); // Black color
        SDL_SetColorKey(sprite_superficie.Get(), SDL_TRUE, color_key);
        
        SDL2pp::Texture sprite_textura(renderer, sprite_superficie);
        
       

        texturas.emplace_back(std::move(sprite_textura)); 
    }
}

void frames_salto(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
int frame_width, int frame_height, std::vector<SDL2pp::Texture>& texturas) {
    
    for (int i = 0; i < NUM_FRAMES_MOVIMIENTO_PATO; ++i) {

        SDL_Rect rect_inicial = {i * frame_width, 38, frame_width, frame_height}; 
        
        SDL2pp::Surface sprite_superficie(SDL_CreateRGBSurface(0, frame_width, frame_height, 32, 0, 0, 0, 0));
        
        SDL_BlitSurface(sprite_sheet.Get(), &rect_inicial, sprite_superficie.Get(), nullptr);
        
        SDL2pp::Texture sprite_textura(renderer, sprite_superficie);
        
        texturas.emplace_back(std::move(sprite_textura)); 
    }
}

void frames_acostarse(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
int frame_width, int frame_height, std::vector<SDL2pp::Texture>& texturas) {
    
    for (int i = 0; i < NUM_FRAMES_PATO_ACOSTADO; ++i) {

        SDL_Rect rect_inicial = {i * frame_width, 70, frame_width, frame_height}; 
        
        SDL2pp::Surface sprite_superficie(SDL_CreateRGBSurface(0, frame_width, frame_height, 32, 0, 0, 0, 0));
        
        SDL_BlitSurface(sprite_sheet.Get(), &rect_inicial, sprite_superficie.Get(), nullptr);
        
        SDL2pp::Texture sprite_textura(renderer, sprite_superficie);
        
        texturas.emplace_back(std::move(sprite_textura)); 
    }
}

void pato_camina_derecha(std::vector<SDL2pp::Texture>& movimiento_pato, SDL2pp::Renderer& renderer,
                        SDL_Rect& rect_inicio,SDL2pp::Rect& rect_destino, SDL2pp::Texture& fondo) {
    
    for (int i = 0; i < NUM_FRAMES_MOVIMIENTO_PATO; ++i){
        
        renderer.Clear();
        renderer.Copy(fondo, SDL2pp::Optional<SDL2pp::Rect>(), SDL2pp::Optional<SDL2pp::Rect>());
        rect_destino.x += 2 ;
        renderer.Copy(movimiento_pato[i], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio), SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
        renderer.Present();


        SDL_Delay(70); 
    }

    renderer.Copy(movimiento_pato[0], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio), SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
    
    renderer.Present();
    
}

void pato_salta(std::vector<SDL2pp::Texture>& frames_salto, SDL2pp::Renderer& renderer,
                        SDL_Rect& rect_inicio,SDL2pp::Rect& rect_destino) {
    
    for (int i = 0; i < NUM_FRAMES_SALTA_PATO; ++i){
        rect_destino.y -= 3 ;
        rect_destino.x += 0.5 ;
        renderer.Copy(frames_salto[i], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio), SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
        renderer.Present();


        SDL_Delay(70); 
    }
    renderer.Clear();

    for (int i = 3; i < NUM_FRAMES_BAJA_PATO; ++i){
        rect_destino.y += 1 ;
        rect_destino.x += 0.5 ;
        renderer.Copy(frames_salto[i], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio), SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
        renderer.Present();


        SDL_Delay(70); 
    }

    renderer.Copy(frames_salto[0], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio), SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
    
    renderer.Present();
    
}

void pato_camina_izquierda(std::vector<SDL2pp::Texture>& movimiento_pato, SDL2pp::Renderer& renderer,
SDL_Rect& rect_inicio,SDL2pp::Rect& rect_destino ) {
    
    for (int i = 0; i < NUM_FRAMES_MOVIMIENTO_PATO; ++i){
        renderer.Copy(movimiento_pato[0], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio), SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
        rect_destino.x -= 2 ; //aca no sabemos cuanto nos tenemos que mover realmente, es arbitrario el valor ahora mismo

        SDL_RenderCopyEx(renderer.Get(), movimiento_pato[i].Get(), &rect_inicio, &rect_destino, 0, nullptr, SDL_FLIP_HORIZONTAL);

        renderer.Present();


        SDL_Delay(70); 
    }

    SDL_RenderCopyEx(renderer.Get(), movimiento_pato[0].Get(), &rect_inicio, &rect_destino, 0, nullptr, SDL_FLIP_HORIZONTAL);

    renderer.Present();
    
}

void pato_agachado(std::vector<SDL2pp::Texture>& frames_acostarse, SDL2pp::Renderer& renderer,
                        SDL_Rect& rect_inicio,SDL2pp::Rect& rect_destino) {
    
    for (int i = 0; i < NUM_FRAMES_PATO_ACOSTADO; ++i){
        // rect_destino.y -= 3 ;
        // rect_destino.x += 0.5 ;
        renderer.Copy(frames_acostarse[i], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio), SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
        renderer.Present();


        SDL_Delay(150); 
    }
    renderer.Clear();

    // for (int i = 3; i < NUM_FRAMES_BAJA_PATO; ++i){
    //     // rect_destino.y += 1 ;
    //     // rect_destino.x += 0.5 ;
    //     renderer.Copy(frames_acostarse[i], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio), SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
    //     renderer.Present();


    //     SDL_Delay(150); 
    // }

    renderer.Copy(frames_acostarse[0], SDL2pp::Optional<SDL2pp::Rect>(rect_inicio), SDL2pp::Optional<SDL2pp::Rect>(rect_destino));
    
    renderer.Present();
    
}


int main() {    
    // inicializar el SDL video, lo requiere el SDL_PollEvent en la documentacion:
    // As this function may implicitly call SDL_PumpEvents(), you can only call
    // this function in the thread that initialized the video subsystem.


    std::vector<SDL2pp::Texture> movimiento_pato;
    std::vector<SDL2pp::Texture> salto_pato;
    std::vector<SDL2pp::Texture> acostarse_pato;

	SDL sdl(SDL_INIT_VIDEO);

    // Initialize SDL_image
        IMG_Init(IMG_INIT_PNG);

        // Create main window
        SDL2pp::Window window("SDL2 Image Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_RESIZABLE);
        
        // Create renderer
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

        //lugar de inicio del pato
        SDL2pp::Rect rect_inicio = {1, 8, 32, 32};

        SDL2pp::Surface sprite_fondo(IMG_Load("../resources/forest.webp"));

        SDL2pp::Texture fondo(renderer, sprite_fondo);

        
        SDL2pp::Surface sprite_pato_gris(IMG_Load("../resources/Grey-Duck.png"));
        

        Uint32 color_key = SDL_MapRGBA(sprite_pato_gris.Get()->format, 0, 0, 0, 0); 

        SDL_SetColorKey(sprite_pato_gris.Get(), SDL_TRUE, color_key);

        //conseguir sprites de movimiento
        frames_movimientos(renderer, sprite_pato_gris, PIXEL_PATO, PIXEL_PATO, movimiento_pato);

        frames_salto(renderer, sprite_pato_gris, PIXEL_PATO, PIXEL_PATO, salto_pato);

        frames_acostarse(renderer, sprite_pato_gris, PIXEL_PATO, PIXEL_PATO, acostarse_pato);

        // Clear screen
        renderer.Clear();

        
        SDL2pp::Rect rect_dibujado = {100, 100, 32, 32}; // inicialmente situado en (100, 100)

        // Mostramos el pato sin movimiento, en estado de "espera".
        renderer.Copy(movimiento_pato[0], rect_inicio, rect_dibujado);

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
                    pato_camina_derecha(movimiento_pato, renderer, rect_inicio, rect_dibujado, fondo);   
                    //queue.push(pato_camina_derecha());
                    continue;
                }
                if (evento.key.keysym.sym == SDLK_a) {
                    //aca vendria la logica de moverte para la izquierda.
                    renderer.Clear();
                    pato_camina_izquierda(movimiento_pato, renderer, rect_inicio, rect_dibujado);   
                    continue;
                }
                if (evento.key.keysym.sym == SDLK_w) {
                    //aca vendria la logica de saltar.
                    renderer.Clear();
                    pato_salta(salto_pato, renderer, rect_inicio, rect_dibujado);   
                    continue;
                }
                if (evento.key.keysym.sym == SDLK_s) {
                    
                    //aca vendria la logica de tirarse al piso.
                    renderer.Clear();
                    pato_agachado(acostarse_pato, renderer, rect_inicio, rect_dibujado);   
                    continue;
                }
            }
        }
        renderer.Clear();
        renderer.Copy(fondo, SDL2pp::Optional<SDL2pp::Rect>(), SDL2pp::Optional<SDL2pp::Rect>());
        renderer.Copy(movimiento_pato[0], rect_inicio, rect_dibujado);
        renderer.Present();
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


