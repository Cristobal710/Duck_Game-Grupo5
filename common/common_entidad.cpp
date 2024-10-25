#include "common_entidad.h"

Entidad::Entidad(uint8_t id, uint8_t pos_x, uint8_t pos_y): id(id), pos_x(pos_x), pos_y(pos_y) {}

uint8_t Entidad::get_id() { return id; }

uint8_t Entidad::get_pos_x() { return pos_x; }

uint8_t Entidad::get_pos_y() { return pos_y; }
