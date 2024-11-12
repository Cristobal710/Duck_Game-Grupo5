#include "common_arma.h"

Arma::Arma(uint8_t id, uint8_t pos_x, uint8_t pos_y, uint8_t municion_disponible, uint8_t alcance):
        Entidad(id, pos_x, pos_y),
        municion_disponible(municion_disponible),
        alcance(alcance) {}

void Arma::disparar() { municion_disponible--; }

// std::string Arma::get_nombre() { return nombre; }

uint8_t Arma::get_municion_disponible() { return municion_disponible; }

uint8_t Arma::get_alcance() { return alcance; }

