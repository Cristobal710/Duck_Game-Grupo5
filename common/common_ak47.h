#ifndef AK47_H
#define AK47_H

#include "common_arma.h"

class AK47 : public Arma {
public:
    AK47(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible, uint16_t alcance)
        : Arma(id, pos_x, pos_y, municion_disponible, alcance, AK_47) {}
    bool disparar() override;
};

#endif