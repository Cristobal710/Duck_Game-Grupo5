#include "common_arma.h"

Arma::Arma(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t municion_disponible, uint16_t alcance):
        Entidad(id, pos_x, pos_y),
        municion_disponible(municion_disponible),
        alcance(alcance) {}

void Arma::disparar() { municion_disponible--; }

// std::string Arma::get_nombre() { return nombre; }

uint8_t Arma::get_municion_disponible() { return municion_disponible; }

uint16_t Arma::get_alcance() { return alcance; }

