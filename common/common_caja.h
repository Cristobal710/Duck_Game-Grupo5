#ifndef COMMON_CAJA_H
#define COMMON_CAJA_H
#include "common_arma.h"
#include "common_entidad.h"
#include "common_hitbox.h"
class Caja: public Entidad {
private:
    uint16_t tipo;
    bool esta_vacia;
    Arma arma; 

public:
    Caja();
    Caja(uint16_t id, uint16_t pos_x, uint16_t pos_y, Arma& arma);
    Caja(uint16_t id, uint16_t pos_x, uint16_t pos_y);

    Arma get_arma();
    bool operator==(const Caja& otra) const;
    void calcular_hitbox() override;
    HitBox get_hitbox();
    bool get_esta_vacia();
    void set_esta_vacia(bool esta_vacia);
};

#endif
