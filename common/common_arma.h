#ifndef ARMA_H
#define ARMA_H

#include <string>

#include "common_entidad.h"

class Arma: public Entidad {
protected:
    uint8_t municion_disponible;
    uint16_t alcance;
    uint8_t tipo_arma;

public:
    void calcular_hitbox() override;
    Arma(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible,
         uint16_t alcance, uint8_t tipo_arma);
    void disparar();
    void recargar();
    std::string get_nombre();
    uint8_t get_municion_disponible();
    uint16_t get_alcance();
    uint8_t get_tipo_arma();
};

#endif
