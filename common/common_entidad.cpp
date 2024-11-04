#include "common_entidad.h"

Entidad::Entidad(uint16_t id, uint16_t pos_x, uint16_t pos_y): id(id), pos_x(pos_x), pos_y(pos_y) {}

uint16_t Entidad::get_id() { return id; }

uint16_t Entidad::get_pos_x() { return pos_x; }

uint16_t Entidad::get_pos_y() { return pos_y; }
