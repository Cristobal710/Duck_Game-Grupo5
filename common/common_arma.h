#ifndef ARMA_H
#define ARMA_H

#include <string>

#include "common_entidad.h"

class Arma: public Entidad {
protected:
    uint8_t municion_disponible;
    uint8_t alcance;

public:
    Arma(uint8_t id, uint8_t pos_x, uint8_t pos_y, uint8_t municion_disponible,
         uint8_t alcance);
    void disparar();
    void recargar();
    std::string get_nombre();
    uint8_t get_municion_disponible();
    uint8_t get_alcance();
};

#endif
