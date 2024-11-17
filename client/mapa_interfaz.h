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

class MapaInterfaz {

    private:
    SDL2pp::Renderer& renderer;
    FondoInterfaz fondo;
    //std::unordered_map<int, std::vector<TileInterfaz>> horizontalGroups;
    //std::unordered_map<int, std::vector<TileInterfaz>> verticalGroups;
    std::vector<TileInterfaz> tiles;
    std::vector<PatoInterfaz> patos;
    std::vector<BalaInterfaz> balas;
    bool mapa_procesado;
    Camara camara;

    public:
    MapaInterfaz(SDL2pp::Renderer& renderer);
    int dibujar(int it);
    void set_fondo(std::string fondo_path);
    void agregar_tile(std::string fondo_path, int x, int y);
    void agregar_spawn(uint16_t id_jugador, int x, int y);
    void agregar_bala(std::string path_bala, int x, int y, uint8_t direccion);
    PatoInterfaz& get_pato_con_id(uint16_t id);
    void procesado();
    bool esta_procesado() {return mapa_procesado;};
};


#endif
