#ifndef BALA_INTERFAZ_H
#define BALA_INTERFAZ_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_image.h>
#include <vector>
#include "../common/common_constantes.h"

/*enum class TipoArma {
    Granada,
    Banana,
    Pew_Pew_Laser,
    Laser_Rifle, //balas raras
    AK47,
    Pistola_Duelos,
    Pistola_Cowboy, //esta muy arriba ver px
    Magnum,
    Escopeta,
    Sniper //esta muy arriba ver px
};*/

class BalaInterfaz {
private:
    std::vector<SDL2pp::Texture> bala;
    SDL2pp::Rect rect_inicio_bala;
    SDL2pp::Rect rect_dibujado_bala;
    SDL2pp::Renderer& renderer;
    uint8_t direccion;
    //TipoArma tipo_arma;

    void cargar_frames(SDL2pp::Renderer& renderer, SDL2pp::Surface& sprite_sheet,
                   int offset_y, std::vector<SDL2pp::Texture>& texturas,
                   int num_frames, int offset_x, int pixeles_x, int pixeles_y);


public:
    BalaInterfaz(SDL2pp::Renderer& renderer, const std::string& bala_path, int pos_x, int pos_y, uint8_t direccion);
    void dibujar(int it);

    void set_posicion_bala(uint16_t pos_x_final, uint16_t pos_y_final);

};

#endif