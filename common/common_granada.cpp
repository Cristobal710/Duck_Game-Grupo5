#include "common_granada.h"

Granada::Granada(uint8_t id, uint8_t pos_x, uint8_t pos_y, uint8_t rango):
        Entidad(id, pos_x, pos_y), rango(rango) {}

uint8_t Granada::get_rango() { return rango; }

bool Granada::esta_activa() { return activa; }

bool Granada::get_exploto() { return exploto; }

void Granada::activar() { activa = true; }

void Granada::explotar() { exploto = true; }
