#include "common_arma.h"

#define ANCHO_ARMA 32
#define ALTO_ARMA 32

Arma::Arma(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible, uint16_t alcance, uint8_t tipo_arma):
        Entidad(id, pos_x, pos_y),
        municion_disponible(municion_disponible),
        alcance(alcance),
        tipo_arma(tipo_arma) {
        calcular_hitbox();
        }

void Arma::disparar() { municion_disponible--; }

// std::string Arma::get_nombre() { return nombre; }

uint8_t Arma::get_municion_disponible() { return municion_disponible; }

uint16_t Arma::get_alcance() { return alcance; }

void Arma::calcular_hitbox() {
    hitbox = HitBox(pos_x, pos_y, ALTO_ARMA, ANCHO_ARMA);
}

uint8_t Arma::get_tipo_arma() { return tipo_arma; }
