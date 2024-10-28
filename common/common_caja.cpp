#include "common_caja.h"

Caja::Caja(uint8_t id, uint8_t pos_x, uint8_t pos_y, uint8_t recompensa):
        Entidad(id, pos_x, pos_y),
        recompensa(recompensa),
        esta_vacia(false) {}

uint8_t Caja::get_recompensa() {
    return recompensa;
}
