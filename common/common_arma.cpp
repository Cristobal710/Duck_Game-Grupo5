#include "common_arma.h"

#define ANCHO_ARMA 32
#define ALTO_ARMA 32

Arma::Arma(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible, uint16_t alcance, uint8_t tipo_arma):
        Entidad(id, pos_x, pos_y),
        municion_disponible(municion_disponible),
        alcance(alcance),
        tipo_arma(tipo_arma),
        se_agarro(false) {
        calcular_hitbox();
        }

bool Arma::disparar() {
    if (municion_disponible > 0) {
        municion_disponible--;
        return true;
    }
    return false;
}

// std::string Arma::get_nombre() { return nombre; }

uint8_t Arma::get_municion_disponible() { return municion_disponible; }

uint16_t Arma::get_alcance() { return alcance; }

void Arma::calcular_hitbox() {
    hitbox = HitBox(pos_x, pos_y, ANCHO_ARMA, ALTO_ARMA);
}

uint8_t Arma::get_tipo_arma() { return tipo_arma; }

bool Arma::operator==(const Arma& otra) const {
    return id == otra.id && pos_x == otra.pos_x && pos_y == otra.pos_y && tipo_arma == otra.tipo_arma && municion_disponible == otra.municion_disponible;
}

bool Arma::get_se_agarro(){
    return se_agarro;
}

void Arma::set_se_agarro(bool agarrado){
    se_agarro = agarrado;
}