#ifndef BALA_H
#define BALA_H

#include "common_entidad.h"
#include "common_tipo_colision.h"

class Bala: public Entidad {
protected:
    uint16_t pos_x_final;
    uint16_t pos_y_final;
    uint8_t direccion;
    uint8_t tipo_arma;
    uint16_t id_origen;

public:
    void calcular_hitbox() override;
    Bala();
    Bala(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint16_t pos_x_final, uint16_t pos_y_final,
           uint8_t direccion, uint8_t tipo_arma);
         
    Bala(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint16_t pos_x_final, uint16_t pos_y_final,
           uint8_t direccion, uint8_t tipo_arma, uint16_t id_origen);
    void set_pos_x(uint16_t pos_x);
    void set_pos_y(uint16_t pos_y);
    uint16_t get_pos_x_final();
    uint16_t get_pos_y_final();
    uint8_t get_direccion();
    uint16_t get_id_origen();
    uint8_t get_tipo_arma();
    TipoColision colisiona_con_tile(SDL2pp::Rect hitbox_tile);
};

#endif
