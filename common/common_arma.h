#ifndef ARMA_H
#define ARMA_H

#include <string>

#include "common_entidad.h"

class Arma: public Entidad {
protected:
    uint8_t municion_disponible;
    uint16_t alcance;

public:
    void calcular_hitbox() override;
    Arma(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible,
         uint16_t alcance);
    void disparar();
    void recargar();
    std::string get_nombre();
    uint8_t get_municion_disponible();
    uint16_t get_alcance();
};

#endif
