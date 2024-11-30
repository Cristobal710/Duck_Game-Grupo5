#ifndef SNIPER_H
#define SNIPER_H

#include "common_arma.h"

class Sniper : public Arma {
public:
    Sniper(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible, uint16_t alcance)
        : Arma(id, pos_x, pos_y, municion_disponible, alcance, SNIPER) {}
    bool disparar() override;
};

#endif