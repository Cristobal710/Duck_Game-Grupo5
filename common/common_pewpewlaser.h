#ifndef PEWPEWLASER_H
#define PEWPEWLASER_H

#include "common_arma.h"

class PewPewLaser : public Arma {
public:
    PewPewLaser(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible, uint16_t alcance)
        : Arma(id, pos_x, pos_y, municion_disponible, alcance, PEW_PEW_LASER) {}
    bool disparar() override;
};

#endif