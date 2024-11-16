#include "mapa_interfaz.h"
#include <utility>
MapaInterfaz::MapaInterfaz(SDL2pp::Renderer& renderer): 
renderer(renderer), fondo(renderer, "../resources/backgrounds/city.png"), tiles(),
patos(), balas(), mapa_procesado(false), camara(1280, 720)
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

void MapaInterfaz::agregar_bala(std::string path_bala, int x, int y, uint8_t direccion) {
    BalaInterfaz bala(renderer, path_bala, x, y, direccion);
    balas.emplace_back(std::move(bala));
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

void MapaInterfaz::dibujar(int it){

    if (!patos.empty()){
        PatoInterfaz& pato_cliente = patos.front();
        
        camara.actualizar(pato_cliente, patos);
    }
    float zoom_factor = camara.obtener_zoom();

    SDL2pp::Rect posicion_camara = camara.obtener_rect_camara();

    
    fondo.dibujar(zoom_factor, posicion_camara.x, posicion_camara.y);

    for (TileInterfaz& tile : tiles){
        tile.dibujar(zoom_factor);
    }
    for (PatoInterfaz& pato : patos){
        pato.dibujar(it, zoom_factor);
    }
    for (BalaInterfaz& bala : balas){
        bala.dibujar(it);
    }
    balas.clear();
}

