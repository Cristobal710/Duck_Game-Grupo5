#ifndef ESCOPETA_H
#define ESCOPETA_H

#include "common_arma.h"

class Escopeta : public Arma {
public:
    Escopeta(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible, uint16_t alcance)
        : Arma(id, pos_x, pos_y, municion_disponible, alcance, ESCOPETA) {}
    bool disparar() override;
};

#endif