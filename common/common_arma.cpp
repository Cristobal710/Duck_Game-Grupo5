#include "common_arma.h"

Arma::Arma(uint8_t id, uint8_t pos_x, uint8_t pos_y, std::string nombre,
           uint8_t municion_disponible, uint8_t balas_max, uint8_t alcance):
        Entidad(id, pos_x, pos_y),
        nombre(nombre),
        municion_disponible(municion_disponible),
        balas_max(balas_max),
        alcance(alcance) {}

void Arma::disparar() { municion_disponible--; }

void Arma::recargar() { municion_disponible = balas_max; }

std::string Arma::get_nombre() { return nombre; }

uint8_t Arma::get_municion_disponible() { return municion_disponible; }

uint8_t Arma::get_balas_max() { return balas_max; }

uint8_t Arma::get_alcance() { return alcance; }
