#include "common_caja.h"

#define ANCHO_CAJA 16
#define ALTO_CAJA 16

Caja::Caja(): Entidad(0, 0, 0), recompensa(0), esta_vacia(true){}

Caja::Caja(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t recompensa):
        Entidad(id, pos_x, pos_y), recompensa(recompensa), esta_vacia(false) {
                calcular_hitbox();
        }

bool Caja::get_esta_vacia(){return esta_vacia;}

bool Caja::operator==(const Caja& otra) const {
    return id == otra.id && pos_x == otra.pos_x && pos_y == otra.pos_y;
}

uint8_t Caja::get_recompensa() { return recompensa; }

void Caja::calcular_hitbox() {
    hitbox = HitBox(pos_x, pos_y, ANCHO_CAJA, ALTO_CAJA);
}
HitBox Caja::get_hitbox(){return hitbox;}