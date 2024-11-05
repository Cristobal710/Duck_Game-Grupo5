#include "movimiento_lateral.h"
#include "../common/common_constantes.h"

#define NUM_FRAMES_MOVIMIENTO_PATO 6
#define PIXEL_PATO 32


MovimientoLateral::MovimientoLateral(SDL2pp::Renderer& renderer, const std::string& pato_path, 
int pos_x, int pos_y):
movimiento_pato(),
puntero_movimiento_derecha(0),
puntero_movimiento_izquierda(0),
rect_inicio(1, 8, PIXEL_PATO, PIXEL_PATO),
rect_dibujado(pos_x, pos_y, PIXEL_PATO, PIXEL_PATO),
renderer(renderer) 
{
    SDL2pp::Surface sprite_pato(IMG_Load(pato_path.c_str()));
    frames_movimientos(renderer, sprite_pato);
}


void MovimientoLateral::frames_movimientos(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet) {
        cargar_frames(renderer, sprite_sheet, 6, movimiento_pato, NUM_FRAMES_MOVIMIENTO_PATO);                                           
    }


void MovimientoLateral::mostrar_frame_derecha(int it) {
    if (it > NUM_FRAMES_MOVIMIENTO_PATO){
    renderer.Copy(movimiento_pato[(it % NUM_FRAMES_MOVIMIENTO_PATO)], rect_inicio,
        rect_dibujado);
    return;
    }
    renderer.Copy(movimiento_pato[(it)], rect_inicio,
        rect_dibujado);
    
}

void MovimientoLateral::mostrar_frame_izquierda(int it) {
    puntero_movimiento_izquierda++;
    if (puntero_movimiento_izquierda == 6){
        puntero_movimiento_izquierda = 0;
    }
    if (it > NUM_FRAMES_MOVIMIENTO_PATO){
    SDL_RenderCopyEx(renderer.Get(), movimiento_pato[it % NUM_FRAMES_MOVIMIENTO_PATO].Get(), &rect_inicio, &rect_dibujado, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);
    return;
    }
    SDL_RenderCopyEx(renderer.Get(), movimiento_pato[it].Get(), &rect_inicio, &rect_dibujado, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);
    
    
}

SDL2pp::Texture& MovimientoLateral::mostrar_frame() { return movimiento_pato[0]; }

void MovimientoLateral::pato_movimiento(uint8_t& movimiento, uint8_t& direccion_pato, int pos_x, int pos_y, int it) {
    if (movimiento == MOVER_DERECHA){
        rect_dibujado.SetX(pos_x);
        rect_dibujado.SetY(pos_y);
        mostrar_frame_derecha(it);
       
    
    } else if (movimiento == MOVER_IZQUIERDA) {
        rect_dibujado.SetX(pos_x);
        rect_dibujado.SetY(pos_y);
        mostrar_frame_izquierda(it);
        
    } else {
        puntero_movimiento_derecha = 0;
        puntero_movimiento_izquierda = 0;

        if (direccion_pato == DIRECCION_IZQUIERDA) {
            SDL_RenderCopyEx(renderer.Get(), movimiento_pato[puntero_movimiento_izquierda].Get(), &rect_inicio, &rect_dibujado, 0,
                nullptr, SDL_FLIP_HORIZONTAL);
        } else {
            renderer.Copy(mostrar_frame(), rect_inicio, rect_dibujado);
        }
        //renderer.Copy(mostrar_frame(), rect_inicio, rect_dibujado);
    }
}


void MovimientoLateral::cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
                                 int offset_y, std::vector<SDL2pp::Texture>& texturas,
                                 int num_frames) {
    for (int i = 0; i < num_frames; ++i) {

        SDL_Rect rect_inicial = {i * PIXEL_PATO, offset_y, PIXEL_PATO, PIXEL_PATO};

        SDL2pp::Surface sprite_superficie(
                SDL_CreateRGBSurface(0, PIXEL_PATO, PIXEL_PATO, 32, 0, 0, 0, 0));

        SDL_BlitSurface(sprite_sheet.Get(), &rect_inicial, sprite_superficie.Get(), nullptr);

        Uint32 color_key = SDL_MapRGB(sprite_superficie.Get()->format, 0, 0, 0);

        SDL_SetColorKey(sprite_superficie.Get(), SDL_TRUE, color_key);

        SDL2pp::Texture sprite_textura(renderer, sprite_superficie);

        texturas.emplace_back(std::move(sprite_textura));
    }
}
