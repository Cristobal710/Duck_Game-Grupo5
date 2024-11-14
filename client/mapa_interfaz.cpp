#include "mapa_interfaz.h"
#include <utility>
MapaInterfaz::MapaInterfaz(SDL2pp::Renderer& renderer): 
renderer(renderer), fondo(renderer, "../resources/backgrounds/city.png"), tiles()
{}

void MapaInterfaz::set_fondo(std::string fondo_path) {
    fondo = FondoInterfaz(renderer, fondo_path);
}

void MapaInterfaz::agregar_tile(std::string tile_path, int x, int y){
    TileInterfaz tile(renderer, tile_path, x, y);
    tiles.emplace_back(std::move(tile));
}

void MapaInterfaz::dibujar(int x1, int y1, int x2, int y2){
    fondo.dibujar(1.0f, 2.0f, x1, y1, x2, y2);
    for (TileInterfaz& tile : tiles){
        tile.dibujar();
    }
}

