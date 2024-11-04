#ifndef COMMON_CAJA_H
#define COMMON_CAJA_H
#include "common_arma.h"
#include "common_entidad.h"

class Caja: public Entidad {
private:
    uint16_t tipo;
    uint16_t recompensa;
    bool esta_vacia;

public:
    Caja(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t recompensa);
    uint8_t get_recompensa();
};

#endif
