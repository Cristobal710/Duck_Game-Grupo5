#include "mapa_interfaz.h"
#include <utility>
MapaInterfaz::MapaInterfaz(SDL2pp::Renderer& renderer): 
renderer(renderer), fondo(renderer, "../resources/backgrounds/city.png"), tiles(),
patos(), mapa_procesado(false)
{}

void MapaInterfaz::set_fondo(std::string fondo_path) {
    fondo = FondoInterfaz(renderer, fondo_path);
}

void MapaInterfaz::agregar_tile(std::string tile_path, int x, int y){
    TileInterfaz tile(renderer, tile_path, x, y);
    tiles.emplace_back(std::move(tile));
}

void MapaInterfaz::agregar_spawn(std::string id_jugador, int x, int y) {
    id_jugador.clear();
    PatoInterfaz pato(renderer, "../resources/Grey-Duck.png", x, y, 3);
    patos.emplace_back(std::move(pato));
}

PatoInterfaz& MapaInterfaz::get_pato_con_id(uint16_t id) {
    for (PatoInterfaz& pato : patos){
        if (pato.mismo_id(id)){
            return  pato;
        }
    }
    
    // If no matching object was found, throw an exception
    throw std::runtime_error("Pato with the given id not found.");
}

void MapaInterfaz::procesado() {
    mapa_procesado = true;
}

void MapaInterfaz::dibujar(int x1, int y1, int x2, int y2, int it){
    fondo.dibujar(1.0f, 2.0f, x1, y1, x2, y2);
    for (TileInterfaz& tile : tiles){
        tile.dibujar();
    }
    for (PatoInterfaz& pato : patos){
        pato.dibujar(it, 2.0f);
    }
}

