#ifndef MAGNUM_H
#define MAGNUM_H

#include "common_arma.h"

class Magnum : public Arma {
public:
    Magnum(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible, uint16_t alcance)
        : Arma(id, pos_x, pos_y, municion_disponible, alcance, MAGNUM) {}
    bool disparar() override;
};

#endif