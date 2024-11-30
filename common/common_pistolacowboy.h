#ifndef PISTOLACOWBOY_H
#define PISTOLACOWBOY_H

#include "common_arma.h"

class PistolaCowboy : public Arma {
public:
    PistolaCowboy(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible, uint16_t alcance)
        : Arma(id, pos_x, pos_y, municion_disponible, alcance, PISTOLA_COWBOY) {}
    bool disparar() override;
};

#endif