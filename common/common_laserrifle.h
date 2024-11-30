#ifndef LASERRIFLE_H
#define LASERRIFLE_H

#include "common_arma.h"

class LaserRifle : public Arma {
public:
    LaserRifle(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible, uint16_t alcance)
        : Arma(id, pos_x, pos_y, municion_disponible, alcance, LASER_RIFLE) {}
    bool disparar() override;
};

#endif