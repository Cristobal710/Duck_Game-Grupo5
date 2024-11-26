#ifndef COMMON_CAJA_H
#define COMMON_CAJA_H
#include "common_arma.h"
#include "common_entidad.h"
#include "common_hitbox.h"
class Caja: public Entidad {
private:
    uint16_t tipo;
    uint8_t recompensa;
    bool esta_vacia;
    Arma* arma; 

public:
    Caja();
    Caja(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t recompensa, Arma* arma);
    Caja(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t recompensa);

    uint8_t get_recompensa();
    Arma* get_arma();
    bool operator==(const Caja& otra) const;
    void calcular_hitbox() override;
    HitBox get_hitbox();
    bool get_esta_vacia();
    void set_esta_vacia(bool esta_vacia);
};

#endif
