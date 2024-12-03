#include "mapa_interfaz.h"
#define WIDTH_SCREEN 1280
#define HEIGHT_SCREEN 720

MapaInterfaz::MapaInterfaz(SDL2pp::Renderer& renderer, uint16_t id_jugador_principal)
    : renderer(renderer), 
    superficie(SDL2pp::Surface(SDL_CreateRGBSurface(0, 1280, 720, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000))),  // Initialize superficie properly
    fondo(superficie, "../resources/backgrounds/city.png"),
    tiles(),
    patos(), 
    balas(), 
    cajas(),
    armas(),
    protecciones(),
    id_pato(id_jugador_principal) 
{}

void MapaInterfaz::set_fondo(std::string fondo_path) {
    fondo.set_fondo(fondo_path);
}

void MapaInterfaz::agregar_tile(std::string tile_path, int x, int y){
    TileInterfaz tile(superficie, tile_path, x, y);
    tiles.emplace_back(std::move(tile));
}

SDL_Color MapaInterfaz::generar_color(int index) {
    if(index == 1){
        index = 30;
    } else if (index == 2){
        index = 35;
    }
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

void MapaInterfaz::agregar_caja(int x, int y) {
    CajaInterfaz caja(superficie, "../resources/boxes/Box_.png", x, y);
    cajas.emplace_back(std::move(caja));
}

void MapaInterfaz::agregar_arma(uint16_t id, int x, int y, uint8_t tipo_arma){
    std::string path_arma;
    obtener_tipo_arma(tipo_arma, path_arma);
    ArmaInterfaz arma(superficie, path_arma, x, y, id);
    armas.emplace_back(std::move(arma));
}

void MapaInterfaz::obtener_tipo_arma(uint8_t tipo_arma, std::string& arma_path) {
    if (tipo_arma == GRANADA){
        arma_path =  "../resources/weapons/grenadeLauncher.png";
    } else if (tipo_arma == BANANA){
        arma_path = "../resources/weapons/bananaMano.png";
    } else if (tipo_arma == PEW_PEW_LASER){
        arma_path = "../resources/weapons/pewpewLaser.png";
    } else if (tipo_arma == LASER_RIFLE){
        arma_path = "../resources/weapons/laserRifle.png";
    } else if (tipo_arma == AK_47){
        arma_path = "../resources/weapons/ak47.png";
    } else if (tipo_arma == PISTOLA_DE_DUELOS){
        arma_path = "../resources/weapons/combatShotgun.png";
    } else if (tipo_arma == PISTOLA_COWBOY){
        arma_path = "../resources/weapons/cowboyPistol.png";
    } else if (tipo_arma == MAGNUM){
        arma_path = "../resources/weapons/magnum.png";
    } else if (tipo_arma == ESCOPETA){
        arma_path = "../resources/weapons/shotgun.png";
    } else if (tipo_arma == SNIPER){
        arma_path = "../resources/weapons/sniper.png";
    }
}

void MapaInterfaz::agregar_proteccion(int x, int y, TipoProteccion tipo) {
    std::string path;
    if(tipo == ARMADURA_ENUM){
        path = "../resources/armors/chestPlatePickup.png"; 
    } else if (tipo == CASCO_ENUM){
        path = "../resources/armors/knightHelmet.png";
    }

    EquipamientoInterfaz equipamiento(superficie, path, x, y);
    protecciones.emplace_back(std::move(equipamiento));
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

int MapaInterfaz::cant_patos() { return patos.size(); }

float MapaInterfaz::calcular_distancia( PatoInterfaz& pato_princiapl,  PatoInterfaz& otro_pato)  {
    // Usamos el centro de los rectángulos para calcular la distancia

    float x1 = pato_princiapl.pos_x() + pato_princiapl.get_w() / 2;
    float y1 = pato_princiapl.pos_y() + pato_princiapl.get_h() / 2;
    float x2 = otro_pato.pos_x() + otro_pato.get_w() / 2;
    float y2 = otro_pato.pos_y() + otro_pato.get_h() / 2;

    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

SDL2pp::Rect MapaInterfaz::obtener_rect_dibujar() { 
    SDL2pp::Rect rect_dibujar;
    PatoInterfaz& pato_principal = get_pato_con_id(id_pato);
    float zoom = 1.0f;
    float distancia_maxima = 1.0f;

    if (patos.size() > 1){
        for (auto& pato : patos) {
        float distancia = calcular_distancia(pato_principal, pato);
        distancia_maxima = std::max(distancia_maxima, distancia);
        }
    }

    zoom = 1.0f / (distancia_maxima / 500.0f);  
    zoom = std::max(1.0f, std::min(zoom, 2.0f));  

    int render_width = static_cast<int>(WIDTH_SCREEN / zoom);
    int render_height = static_cast<int>(HEIGHT_SCREEN / zoom);

    int center_x = pato_principal.pos_x() + pato_principal.get_w() / 2;
    int center_y = pato_principal.pos_y() + pato_principal.get_h() / 2;

    rect_dibujar.x = center_x - render_width / 2;  
    rect_dibujar.y = center_y - render_height / 2;

    rect_dibujar.x = std::max(0, std::min(rect_dibujar.x, WIDTH_SCREEN - render_width));
    rect_dibujar.y = std::max(0, std::min(rect_dibujar.y, HEIGHT_SCREEN - render_height));

    rect_dibujar.w = render_width;
    rect_dibujar.h = render_height;

    return rect_dibujar; 
}

void MapaInterfaz::dibujar(int it){

    fondo.dibujar();

    for (auto& tile : tiles) {
        tile.dibujar();
    }

    for (CajaInterfaz& caja : cajas){
        caja.dibujar();
    }

    for (EquipamientoInterfaz& proteccion : protecciones){
        proteccion.dibujar();
    }

    if(!armas.empty()){
        for(ArmaInterfaz& arma : armas){
            uint8_t direccion = DIRECCION_DERECHA;
            arma.dibujar(direccion);
        }        
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
    //armas.clear();
    //cajas.clear();

    SDL2pp::Rect rect_dibujar = obtener_rect_dibujar();
    SDL2pp::Rect rect_superficie(0, 0, 1280, 720);
    SDL2pp::Texture texture(renderer, superficie);
    renderer.Copy(texture,
        SDL2pp::Optional<SDL2pp::Rect>(rect_dibujar), 
        SDL2pp::Optional<SDL2pp::Rect>(rect_superficie) 
    );
}

void MapaInterfaz::caja_recogida(int pos_x, int pos_y){
    for (CajaInterfaz& caja : cajas){
        if (caja.misma_caja(pos_x, pos_y)){
            caja.no_dibujar();
        }
    }
}

void MapaInterfaz::agregar_equipamiento(std::string& equipamiento_path, int x, int y) {
    EquipamientoInterfaz equipamiento(superficie, equipamiento_path, x, y);
    protecciones.emplace_back(std::move(equipamiento));
}

void MapaInterfaz::equip_recogido(int x, int y) {
    for (EquipamientoInterfaz& equip : protecciones){
        if (equip.mismo_equip(x, y)){
            equip.no_dibujar();
        }
    }
}

bool MapaInterfaz::existe_arma(uint16_t id){
    for (ArmaInterfaz& arma : armas){
        if(arma.mismo_arma(id)){
            return true;
        }
    }
    return false;
}

void MapaInterfaz::actualizar_estado_arma(uint16_t id, int x, int y, bool se_agarro){
    for (ArmaInterfaz& arma : armas) {
        if(arma.mismo_arma(id)){
            arma.set_posicion(x, y);
            if(!se_agarro){
                arma.soltar();
            }
        }
    }
}

void MapaInterfaz::arma_recogida(uint16_t id){
    for (ArmaInterfaz& arma : armas) {
        if(arma.mismo_arma(id)){
            arma.no_dibujar();
        }
    }
}

void MapaInterfaz::limpiar_mapa() {
    if (!patos.empty()){
        patos.clear();
    }
    if (!tiles.empty()){
        tiles.clear();
    }
    if (!balas.empty()){
        balas.clear();
    }
    if (!cajas.empty()){
        cajas.clear();
    }
    if(!armas.empty()){
        armas.clear();
    }
    if (!protecciones.empty()){
        protecciones.clear();
    }
    renderer.Clear();
}

uint16_t MapaInterfaz::get_id_pato_principal() { return id_pato; }
