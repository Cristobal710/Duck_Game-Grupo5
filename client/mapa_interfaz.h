#ifndef MAPA_INTERFAZ_H
#define MAPA_INTERFAZ_H
#include <string>
#include <vector>
#include "fondo_interfaz.h"
#include "tile_interfaz.h"
#include <SDL2pp/SDL2pp.hh>

class MapaInterfaz {

    private:
    SDL2pp::Renderer& renderer;
    FondoInterfaz fondo;
    std::vector<TileInterfaz> tiles;
    

    public:
    MapaInterfaz(SDL2pp::Renderer& renderer);
    void dibujar(int x1, int y1, int x2, int y2);
    void set_fondo(std::string fondo_path);
    void agregar_tile(std::string fondo_path, int x, int y);
};


#endif
