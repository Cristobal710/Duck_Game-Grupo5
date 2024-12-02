#ifndef COMMON_PROTECCION_H
#define COMMON_PROTECCION_H

#include "common_tipo_proteccion.h"
#include "common_entidad.h"
 
class Proteccion : public Entidad {
private:
    TipoProteccion tipo;
    bool se_agarro;

public:
    Proteccion(uint16_t id, uint16_t pos_x, uint16_t pos_y, TipoProteccion tipo, bool se_agarro);

    virtual ~Proteccion() {};

    TipoProteccion get_tipo(); 

    bool get_se_agarro();
    void set_se_agarro(bool valor);

    void calcular_hitbox() override;
    HitBox get_hitbox();
};

#endif