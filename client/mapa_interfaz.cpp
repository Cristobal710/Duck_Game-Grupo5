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
    
    //tiles.emplace_back(std::move(tile));
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


    std::unordered_map<int, std::vector<TileInterfaz>> horizontalGroups;
   
    std::unordered_map<int, std::vector<TileInterfaz>> verticalGroups;

    if (!tiles.empty()){
        for (auto& tile : tiles) {
        horizontalGroups[tile.get_pos_y()].push_back(std::move(tile));
        verticalGroups[tile.get_pos_x()].push_back(std::move(tile));
        }

    //zoom_factor = 2.0f;
    // int tamanio_tile = 16 * zoom_factor; 
    // int pos_x = 0;
    // int pos_y = 0;
    //int contador = 0;
    // Iterate over horizontal groups (same y-value)
        for (auto& rowGroup : horizontalGroups) {
            int y = rowGroup.first;  // The common y-coordinate for this row
            int x_offset = 0;  // Offset for each tile in the row

            for (auto& tile : rowGroup.second) {
                int x = tile.get_pos_x() + x_offset * (1280 * zoom_factor);  // Increment x by zoomed width
                tile.dibujar(zoom_factor, x, y);
                x_offset++;  // Move to the next tile in the row
            }
        }

        // Iterate over vertical groups (same x-value)
        for ( auto& colGroup : verticalGroups) {
            int x = colGroup.first;  // The common x-coordinate for this column
            int y_offset = 0;  // Offset for each tile in the column

            for ( auto& tile : colGroup.second) {
                int y = tile.get_pos_y() + y_offset * (720 * zoom_factor);  // Increment y by zoomed height
                tile.dibujar(zoom_factor, x, y);
            }
        }
    }
    
    // for (TileInterfaz& tile : tiles){
    //     pos_x = tile.get_pos_x() + (tamanio_tile - 16) * contador;
    //     //pos_y = tile.get_pos_y() + (tamanio_tile - 16) * contador;
    //     //std::cout << "posicion en x: " << pos_x << " ////";
    //     tile.dibujar(zoom_factor, pos_x, pos_y);
    //     contador++;
    // }
    for (PatoInterfaz& pato : patos){
        pato.dibujar(it, zoom_factor);
    }
    for (BalaInterfaz& bala : balas){
        bala.dibujar(it);
    }
    balas.clear();
}

