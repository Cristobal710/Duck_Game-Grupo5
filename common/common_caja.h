#ifndef COMMON_CAJA_H
#define COMMON_CAJA_H
#include "common_entidad.h"
#include "common_arma.h"

class Caja : public Entidad{
    private:
        uint8_t tipo;
        uint8_t recompensa;
        bool esta_vacia;
    public:
        Caja(uint8_t id, uint8_t pos_x, uint8_t pos_y, uint8_t recompensa);
        uint8_t get_recompensa();
};

#endif
