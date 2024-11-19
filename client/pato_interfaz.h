#ifndef PATO_INTERFAZ_H
#define PATO_INTERFAZ_H
#include <iostream>
#include <vector>
#include "movimiento_lateral.h"
#include "movimiento_salto.h"
#include "movimiento_agachado.h"
#include <SDL2/SDL_image.h>
#include "entidad_interfaz.h"
#include <SDL2pp/SDL2pp.hh>
#include <cstdint>
#include "arma_interfaz.h"
#include "armadura_interfaz.h"
#include "casco_interfaz.h"

enum class TipoArma {
    Granada,
    Banana,
    Pew_Pew_Laser,
    Laser_Rifle, //balas raras
    AK47,
    Pistola_Duelos,
    Pistola_Cowboy, //esta muy arriba ver px
    Magnum,
    Escopeta,
    Sniper //esta muy arriba ver px
};

class PatoInterfaz : public EntidadInterfaz{
private:
    bool vivo;
    uint8_t estado_pato_movimiento;
    uint8_t estado_pato_salto;
    uint8_t direccion_pato;
    uint8_t se_tira_al_piso;
    uint8_t estado_arma;
    uint8_t estado_balas;
    bool armadura_equipada;
    bool casco_equipado;
    SDL2pp::Renderer& renderer;
    SDL2pp::Rect rect_dibujado;
    MovimientoLateral movimiento_pato_lateral;
    MovimientoSalto movimiento_pato_salto;
    MovimientoAgachado movimiento_pato_agachado;
    uint8_t municion_disponible;
    TipoArma tipo_arma;
    uint16_t id_jugador;
    SDL_Color color;

    ArmaInterfaz tomar_arma();

public:
    PatoInterfaz(SDL2pp::Renderer& renderer, const std::string& pato_path, int pos_x, int pos_y, uint16_t pato_id, SDL_Color color);
    ~PatoInterfaz() override = default;
    
     // Move constructor
    PatoInterfaz(PatoInterfaz&& other) noexcept;

    
    void dibujar(int it, float zoom_factor) override;

    void actualizar_estado(uint8_t estado_nuevo, std::string tipo_estado);
    void actualizar_posicion(int pos_x, int pos_y);
    void actualizar_equipamiento(uint8_t estado_nuevo, std::string tipo_estado);
    void set_tipo_arma(TipoArma tipo_arma);
    bool mismo_id(uint16_t id);
    void set_esta_vivo(bool estado);
    bool esta_vivo();
    void dibujar_muerto(float zoom_factor);
    int pos_x();
    int pos_y();
    int get_w();
    int get_h();
};

#endif  // PATO_INTERFAZ_H
