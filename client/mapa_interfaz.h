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
#include "../common/common_tipo_proteccion.h"

class MapaInterfaz {
private:
    SDL2pp::Renderer& renderer;
    SDL2pp::Surface superficie;
    FondoInterfaz fondo;
    std::vector<TileInterfaz> tiles;
    std::vector<PatoInterfaz> patos;
    std::vector<BalaInterfaz> balas;
    std::vector<CajaInterfaz> cajas;
    std::vector<ArmaInterfaz> armas;
    std::vector<EquipamientoInterfaz> protecciones;
    bool mapa_procesado;
    uint16_t id_pato;

    SDL_Color generar_color(int index);
    void obtener_tipo_bala(uint8_t tipo_arma, std::string& path_bala);

    float calcular_distancia(PatoInterfaz& pato_princiapl, PatoInterfaz& otro_pato);
    SDL2pp::Rect obtener_rect_dibujar();

public:
    MapaInterfaz(SDL2pp::Renderer& renderer, uint16_t id_jugador_principal);
    void dibujar(int it);
    
    void set_fondo(std::string fondo_path);
    void agregar_tile(std::string fondo_path, int x, int y);
    void agregar_spawn(uint16_t id_jugador, int x, int y);
    void agregar_caja(int x, int y);
    void agregar_arma(uint16_t id, int x, int y, uint8_t tipo_arma);
    void agregar_proteccion(int x, int y, TipoProteccion tipo);
    void agregar_bala(uint8_t tipo_arma, int x, int y, uint8_t direccion);
    void agregar_equipamiento(std::string& path, int x, int y);
    void caja_recogida(int x, int y);
    void equip_recogido(int x, int y);
    PatoInterfaz& get_pato_con_id(uint16_t id);
    void obtener_tipo_arma(uint8_t tipo_arma, std::string& arma_path);
    bool existe_arma(uint16_t id);
    void procesado();
    bool esta_procesado() {return mapa_procesado;};
    void actualizar_estado_arma(uint16_t id, int x, int y, bool se_agarro);
    void arma_recogida(uint16_t id);

    int cant_patos();
};


#endif
