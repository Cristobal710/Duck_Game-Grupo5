#include "mapa_interfaz.h"

MapaInterfaz::MapaInterfaz(SDL2pp::Renderer& renderer)
    : renderer(renderer), 
    superficie(SDL2pp::Surface(SDL_CreateRGBSurface(0, 1280, 720, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000))),  // Initialize superficie properly
    fondo(superficie, "../resources/backgrounds/city.png"),
    tiles(),
    patos(), 
    balas(), 
    cajas(),
    armas(),
    mapa_procesado(false)
{}

void MapaInterfaz::set_fondo(std::string fondo_path) {
    fondo.set_fondo(fondo_path);
}

void MapaInterfaz::agregar_tile(std::string tile_path, int x, int y){
    TileInterfaz tile(superficie, tile_path, x, y);
    tiles.emplace_back(std::move(tile));
}

SDL_Color MapaInterfaz::generar_color(int index) {
    uint8_t r = (index * 50) % 256;
    uint8_t g = ((index + 1) * 70) % 256;
    uint8_t b = ((index + 2) * 90) % 256;
    return {r, g, b, 255};
}

void MapaInterfaz::agregar_spawn(uint16_t id_jugador, int x, int y) {
    SDL_Color color = generar_color(id_jugador);
    PatoInterfaz pato(superficie, "../resources/Grey-Duck.png", x, y, id_jugador, color);
    patos.emplace_back(std::move(pato));
}

void MapaInterfaz::agregar_caja(std::string& caja_path, int x, int y) {
    //caja_path = "../resources/TileSets/itemBox.png";
    CajaInterfaz caja(superficie, caja_path, x, y);
    cajas.emplace_back(std::move(caja));
}

void MapaInterfaz::agregar_arma(std::string& arma_path, int x, int y) {
    arma_path = "../resources/weapons/ak47.png"; //no llega bien el path
    ArmaInterfaz arma(superficie, arma_path, x, y);
    armas.emplace_back(std::move(arma));
}

void MapaInterfaz::obtener_tipo_bala(uint8_t tipo_arma, std::string& path_bala){
    if(tipo_arma == GRANADA){
        path_bala = "../resources/Random/explode.png";
    } else if (tipo_arma == BANANA){
        path_bala = "../resources/weapons/bananaPiso.png";
    } else if (tipo_arma == PEW_PEW_LASER){
        path_bala = "../resources/weapons/rafaga.png";
    } else if (tipo_arma == LASER_RIFLE){
        path_bala = "../resources/weapons/rayos.png";
    } else if (tipo_arma == AK_47){
        path_bala = "../resources/weapons/dart.png";
    } else if(tipo_arma == PISTOLA_DE_DUELOS){
        path_bala = "../resources/weapons/dart.png";
    } else if (tipo_arma == PISTOLA_COWBOY){
        path_bala = "../resources/weapons/dart.png";
    } else if (tipo_arma == MAGNUM){
        path_bala = "../resources/weapons/dart.png";
    } else if (tipo_arma == ESCOPETA){
        path_bala = "../resources/weapons/dart.png";
    } else if (tipo_arma == SNIPER){
        path_bala = "../resources/weapons/dart.png";
    }
}

void MapaInterfaz::agregar_bala(uint8_t tipo_arma, int x, int y, uint8_t direccion) {
    std::string path_bala;
    obtener_tipo_bala(tipo_arma, path_bala);
    BalaInterfaz bala(superficie, path_bala, x, y, direccion);
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

    //if (!patos.empty()){
    //    PatoInterfaz& pato_cliente = patos.front();

    fondo.dibujar();

    for (auto& tile : tiles) {
        tile.dibujar();
    }

    for (CajaInterfaz& caja : cajas){
        caja.dibujar();
    }

    uint8_t direccion = DIRECCION_DERECHA;
    for (ArmaInterfaz& arma : armas){
        arma.dibujar(direccion);
    }

    for (PatoInterfaz& pato : patos){
        if(pato.esta_vivo()){
            pato.dibujar(it);
        } else {
            pato.dibujar_muerto();
        }
    }
    
    for (BalaInterfaz& bala : balas){
        bala.dibujar(it);
    }
    balas.clear();

    //calcular que parte de superficie dibujar

    SDL2pp::Texture texture(renderer, superficie);
    renderer.Copy(texture, SDL2pp::Rect(0, 0, superficie.GetWidth(), superficie.GetHeight()));
}

