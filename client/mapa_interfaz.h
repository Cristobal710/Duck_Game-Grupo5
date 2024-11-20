#ifndef MAPA_INTERFAZ_H
#define MAPA_INTERFAZ_H
#include <string>
#include <vector>
#include "fondo_interfaz.h"
#include "tile_interfaz.h"
#include "pato_interfaz.h"
#include "bala_interfaz.h"
#include <SDL2pp/SDL2pp.hh>
#include "camara.h"
#include <unordered_map>
#include <utility>
#include "caja_interfaz.h"

class MapaInterfaz {
private:
    SDL2pp::Renderer& renderer;
    SDL2pp::Surface superficie;
    FondoInterfaz fondo;
    std::vector<TileInterfaz> tiles;
    std::vector<PatoInterfaz> patos;
    std::vector<BalaInterfaz> balas;
    std::vector<CajaInterfaz> cajas;
    bool mapa_procesado;

    SDL_Color generar_color(int index);
    void obtener_tipo_bala(uint8_t tipo_arma, std::string& path_bala);

public:
    MapaInterfaz(SDL2pp::Renderer& renderer);
    void dibujar(int it);
    
    void set_fondo(std::string fondo_path);
    void agregar_tile(std::string fondo_path, int x, int y);
    void agregar_spawn(uint16_t id_jugador, int x, int y);
    void agregar_caja(uint16_t id, int x, int y, std::string path);
    void agregar_bala(uint8_t tipo_arma, int x, int y, uint8_t direccion);
    
    PatoInterfaz& get_pato_con_id(uint16_t id);
    
    void procesado();
    bool esta_procesado() {return mapa_procesado;};
};


#endif
