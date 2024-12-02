#ifndef PISTOLADUELOS_H
#define PISTOLADUELOS_H

#include "common_arma.h"

class PistolaDuelos : public Arma {
public:
    PistolaDuelos(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible, uint16_t alcance)
        : Arma(id, pos_x, pos_y, municion_disponible, alcance, PISTOLA_DE_DUELOS) {}
    bool disparar() override;
};

#endif