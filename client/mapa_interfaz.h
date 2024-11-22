#ifndef MAPA_INTERFAZ_H
#define MAPA_INTERFAZ_H
#include <string>
#include <vector>
#include "fondo_interfaz.h"
#include "tile_interfaz.h"
#include "pato_interfaz.h"
#include "bala_interfaz.h"
#include <SDL2pp/SDL2pp.hh>
#include <utility>
#include "caja_interfaz.h"
#include "arma_interfaz.h"
#include "equipamiento_interfaz.h"

class MapaInterfaz {
private:
    SDL2pp::Renderer& renderer;
    SDL2pp::Surface superficie;
    FondoInterfaz fondo;
    std::vector<TileInterfaz> tiles;
    std::vector<PatoInterfaz> patos;
    std::vector<BalaInterfaz> balas;
    std::vector<CajaInterfaz> cajas;
    std::vector<EquipamientoInterfaz> equipamientos;
    bool mapa_procesado;

    SDL_Color generar_color(int index);
    void obtener_tipo_bala(uint8_t tipo_arma, std::string& path_bala);

    float calcular_distancia(PatoInterfaz& pato_princiapl, PatoInterfaz& otro_pato);
    SDL2pp::Rect obtener_rect_dibujar();

public:
    MapaInterfaz(SDL2pp::Renderer& renderer);
    void dibujar(int it);
    
    void set_fondo(std::string fondo_path);
    void agregar_tile(std::string fondo_path, int x, int y);
    void agregar_spawn(uint16_t id_jugador, int x, int y);
    void agregar_caja(int x, int y);
    void agregar_equipamiento(std::string& equipamiento_path, int x, int y);
    void agregar_bala(uint8_t tipo_arma, int x, int y, uint8_t direccion);
    
    PatoInterfaz& get_pato_con_id(uint16_t id);
    
    void procesado();
    bool esta_procesado() {return mapa_procesado;};
};


#endif
