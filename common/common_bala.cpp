#include "common_bala.h"

Bala::Bala() {}

#define ANCHO_BALA 5
#define ALTO_BALA 5



Bala::Bala(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint16_t pos_x_final, uint16_t pos_y_final,
           uint8_t direccion):
        Entidad(id, pos_x, pos_y),
        pos_x_final(pos_x_final),
        pos_y_final(pos_y_final),
        direccion(direccion){ 
        calcular_hitbox();
        }

Bala::Bala(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint16_t pos_x_final, uint16_t pos_y_final,
           uint8_t direccion, uint16_t id_origen):
        Entidad(id, pos_x, pos_y),
        pos_x_final(pos_x_final),
        pos_y_final(pos_y_final),
        direccion(direccion),
        id_origen(id_origen) { 
        calcular_hitbox();
        }

void Bala::calcular_hitbox() {
    hitbox = HitBox(pos_x, pos_y, ANCHO_BALA, ALTO_BALA);
}

uint16_t Bala::get_pos_x_final() { return pos_x_final; }

uint16_t Bala::get_pos_y_final() { return pos_y_final; }

void Bala::set_pos_x(uint16_t pos_x) { this->pos_x = pos_x; }

void Bala::set_pos_y(uint16_t pos_y) { this->pos_y = pos_y; }

uint16_t Bala::get_id_origen(){return id_origen;}

uint8_t Bala::get_direccion() { return direccion; }