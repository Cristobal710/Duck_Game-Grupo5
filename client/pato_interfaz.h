#ifndef PATO_INTERFAZ_H
#define PATO_INTERFAZ_H

#include <vector>
#include "movimiento_lateral.h"
#include "movimiento_salto.h"
#include "movimiento_agachado.h"
#include <SDL2/SDL_image.h>
#include "entidad_interfaz.h"
#include <SDL2pp/SDL2pp.hh>

class PatoInterfaz : public EntidadInterfaz{
private:
    uint8_t estado_pato_movimiento;
    uint8_t estado_pato_salto;
    uint8_t direccion_pato;
    uint8_t se_tira_al_piso;
    uint8_t arma;
    SDL2pp::Rect rect_dibujado;
    MovimientoLateral movimiento_pato_lateral;
    MovimientoSalto movimiento_pato_salto;
    MovimientoAgachado movimiento_pato_agachado;

public:
    PatoInterfaz(SDL2pp::Renderer& renderer, const std::string& pato_path, int pos_x, int pos_y);

    ~PatoInterfaz() override = default;
    void dibujar(int it, float zoom_factor) override;
    void actualizar_estado(uint8_t estado_nuevo, std::string tipo_estado);
    void actualizar_posicion(int pos_x, int pos_y);
    void actualizar_equipamiento(uint8_t estado_nuevo, std::string tipo_estado);
};

#endif  // PATO_INTERFAZ_H
