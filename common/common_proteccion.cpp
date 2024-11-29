#include "common_proteccion.h"
#define ANCHO_PROTECCION 32
#define ALTO_PROTECCION 32
Proteccion::Proteccion(uint16_t id, uint16_t pos_x, uint16_t pos_y, TipoProteccion tipo, bool se_agarro)
        : Entidad(id, pos_x, pos_y), tipo(tipo), se_agarro(se_agarro) {
            calcular_hitbox();
        }

TipoProteccion Proteccion::get_tipo()  { return tipo; }

bool Proteccion::get_se_agarro()  { return se_agarro; }
void Proteccion::set_se_agarro(bool valor) { se_agarro = valor; }




void Proteccion::calcular_hitbox() {
    hitbox = HitBox(pos_x, pos_y, ANCHO_PROTECCION, ALTO_PROTECCION);
}
HitBox Proteccion::get_hitbox(){return hitbox;}



