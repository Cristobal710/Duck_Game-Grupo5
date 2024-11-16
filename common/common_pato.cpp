#include "common_pato.h"

#include <iostream>
#include <SDL2pp/SDL2pp.hh>

#define ANCHO_PATO 24
#define ALTO_PATO 36

Pato::Pato(){}

Pato::Pato(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t direccion):
        Entidad(id, pos_x, pos_y),
        arma(nullptr),
        tomo_armadura(false),
        tomo_casco(false),
        armadura_equipada(false),
        casco_equipado(false),
        vivo(true),
        apunta_arriba(false),
        direccion(direccion),
        estado(),
        contador_salto(0),
        contador_caer(0) 
        {
    calcular_hitbox();
    // if (color == "rojo") {
    //     this->color = 1;
    // } else if (color == "azul") {
    //     this->color = 2;
    // } else if (color == "verde") {
    //     this->color = 3;
    // } else if (color == "amarillo") {
    //     this->color = 4;
    // } else {
    //     this->color = 0;
    // }
}



void Pato::calcular_hitbox() {
    hitbox = HitBox(pos_x, pos_y, ANCHO_PATO, ALTO_PATO);
}

// Pato::~Pato() { delete arma; }

void Pato::moverse_izquierda() {
    pos_x-=3;
    direccion = DIRECCION_IZQUIERDA;
    estado.set_moviendo_izquierda();
}

void Pato::moverse_derecha() {
    pos_x += 3;
    direccion = DIRECCION_DERECHA;
    estado.set_moviendo_derecha();
}

void Pato::saltar() { 
    pos_y-=15;
    estado.set_saltar();
    contador_salto++;
    if (contador_salto == 5) {
        estado.set_dejar_de_saltar();
        contador_salto = 0;
    }
}

void Pato::planear() { pos_y--; }

void Pato::caer() { 
    pos_y+=3; 
    estado.set_caer();
    contador_caer++;
    if (contador_caer == 5) {
        estado.set_dejar_de_caer();
        contador_caer = 0;
    }
}

void Pato::tomar_arma(Arma* nuevaArma) { arma = nuevaArma; }

void Pato::soltar_arma() { arma = nullptr; }

uint8_t Pato::tiene_arma(){ 
    if (arma != nullptr){
        return TOMAR_ARMA;
    } else{
        return BYTE_NULO;
    }
}

void Pato::disparar() {
    estado.set_disparando();
    // if (arma) {
    //     arma->disparar();
    // } else {
    //     estado.set_dejar_de_disparar();
    //     // Si el pato no tiene un arma, no puede disparar
    // }
}

void Pato::apuntar_arriba() { 
    apunta_arriba = true;
    direccion = DIRECCION_ARRIBA;
 }

void Pato::dejar_de_apuntar_arriba() { apunta_arriba = false; }

bool Pato::esta_apuntando_arriba() { return apunta_arriba; }

void Pato::tirarse_al_piso() {
    estado.set_agacharse();
}
void Pato::levantarse_del_piso(){
    estado.set_dejar_de_agacharse();
}

void Pato::tomar_armadura() { tomo_armadura = true; }

void Pato::tomar_casco() { tomo_casco = true; }

void Pato::equipar_armadura() {
    if (tomo_armadura) {
        armadura_equipada = true;
        tomo_armadura = false;
    }
}

void Pato::equipar_casco() {
    if (tomo_casco) {
        casco_equipado = true;
        tomo_casco = false;
    }
}

bool Pato::get_casco_equipado() { return casco_equipado; }

bool Pato::get_armadura_equipada() { return armadura_equipada; }

void Pato::recibir_danio() {
    // En caso de que el pato solo aguante una bala, entonces hay que hacer que el pato muera
    // sino tiene armadura o casco
    if (casco_equipado) {
        casco_equipado = false;
        return;
    }
    if (armadura_equipada) {
        armadura_equipada = false;
        return;
    }
    morir();
}

uint8_t Pato::get_direccion() { return direccion; }

Arma* Pato::get_arma() { return arma; }

bool Pato::esta_vivo() const { return vivo; }

void Pato::morir() { vivo = false; }

bool Pato::armadura_en_inventario() { return armadura_equipada; }

bool Pato::casco_en_inventario() { return tomo_casco; }

// int Pato::get_color() { return color; }

TipoColision Pato::colisiona_con_tile(SDL2pp::Rect hitbox_tile) {
    if (hitbox.no_colisiona(hitbox_tile)) {
        return Nada;
    }
    if (hitbox.colisiona_arriba_con(hitbox_tile)) {
        std::cout<<"colisiona arriba"<<std::endl;
        return Piso;
    }
    if (hitbox.colisiona_abajo_con(hitbox_tile)) {
        std::cout<<"colisiona abajo"<<std::endl;
        return Techo;
    }
    if (hitbox.colisiona_izquierda_con(hitbox_tile)) {
        std::cout<<"colisiona izq"<<std::endl;
        return Pared;
    }
    if (hitbox.colisiona_derecha_con(hitbox_tile)) {
        std::cout<<"colisiona der"<<std::endl;
        return Pared;
    }
    return Nada;
}
TipoColision Pato::colisiona_con_bala(HitBox hitbox_bala) {
    // if (hitbox.colisiona_arriba_con(hitbox_bala) || hitbox.colisiona_abajo_con(hitbox_bala) || hitbox.colisiona_izquierda_con(hitbox_bala) || hitbox.colisiona_derecha_con(hitbox_bala)) {
    //     return Balas;
    // }
    std::cout << "pos x bala:" << static_cast<int>(hitbox_bala.get_hitbox_rect().x) << std::endl;
    return Nada;
}
