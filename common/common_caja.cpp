#include "common_caja.h"

#define ANCHO_CAJA 16
#define ALTO_CAJA 16

Caja::Caja(): Entidad(0, 0, 0), esta_vacia(true){}

Caja::Caja(uint16_t id, uint16_t pos_x, uint16_t pos_y, Arma* arma):
        Entidad(id, pos_x, pos_y), esta_vacia(false), arma(arma) {
                calcular_hitbox();
        }

Caja::Caja(uint16_t id, uint16_t pos_x, uint16_t pos_y):
Entidad(id, pos_x, pos_y), esta_vacia(false) {
        calcular_hitbox();
}

bool Caja::get_esta_vacia(){return esta_vacia;}

void Caja::set_esta_vacia(bool vacia){esta_vacia = vacia;}

bool Caja::operator==(const Caja& otra) const {
    return id == otra.id && pos_x == otra.pos_x && pos_y == otra.pos_y;
}

void Caja::calcular_hitbox() {
    hitbox = HitBox(pos_x, pos_y, ANCHO_CAJA, ALTO_CAJA);
}
HitBox Caja::get_hitbox(){return hitbox;}

Arma* Caja::get_arma(){
    return arma;
}