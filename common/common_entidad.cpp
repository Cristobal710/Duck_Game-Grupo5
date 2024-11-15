#include "common_entidad.h"

Entidad::Entidad() {}

Entidad::Entidad(uint16_t id, uint16_t pos_x, uint16_t pos_y): id(id), pos_x(pos_x), pos_y(pos_y), hitbox() {}

uint16_t Entidad::get_id() { return id; }

uint16_t Entidad::get_pos_x() { return pos_x; }

uint16_t Entidad::get_pos_y() { return pos_y; }

HitBox Entidad::get_hitbox() { 
    return hitbox; 
}

void Entidad::calcular_hitbox() {}

Entidad::~Entidad() {}
