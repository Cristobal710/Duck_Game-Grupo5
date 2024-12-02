#ifndef ARMA_H
#define ARMA_H

#include <string>

#include "common_entidad.h"
#include "common_constantes.h"

class Arma: public Entidad {
protected:
    uint8_t municion_disponible;
    uint16_t alcance;
    uint8_t tipo_arma;
    bool se_agarro;

public:
    void calcular_hitbox() override;
    Arma();
    Arma(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible,
         uint16_t alcance, uint8_t tipo_arma);
    virtual bool disparar(); // Método virtual
    void recargar();
    void set_pos_x(uint16_t pos_x);
    void set_pos_y(uint16_t pos_y);
    std::string get_nombre();
    uint8_t get_municion_disponible();
    uint16_t get_alcance();
    uint8_t get_tipo_arma();
    bool operator==(const Arma& otra) const;
    bool get_se_agarro();
    void set_se_agarro(bool se_agarro);
    void set_municion_disponible(uint8_t municion_disponible);
};

#endif
