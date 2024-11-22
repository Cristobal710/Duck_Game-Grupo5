#include "common_caja.h"

#define ANCHO_CAJA 40
#define ALTO_CAJA 40


Caja::Caja(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t recompensa):
        Entidad(id, pos_x, pos_y), recompensa(recompensa), esta_vacia(false) {
                calcular_hitbox();
        }

uint8_t Caja::get_recompensa() { return recompensa; }

void Caja::calcular_hitbox() {
    hitbox = HitBox(pos_x, pos_y, ANCHO_CAJA, ALTO_CAJA);
}
HitBox Caja::get_hitbox(){return hitbox;}