#include "common_caja.h"

Caja::Caja(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t recompensa):
        Entidad(id, pos_x, pos_y), recompensa(recompensa), esta_vacia(false) {}

uint8_t Caja::get_recompensa() { return recompensa; }
