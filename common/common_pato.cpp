#include "common_pato.h"

#include <iostream>
#include <SDL2pp/SDL2pp.hh>

#define ANCHO_PATO 24
#define ALTO_PATO 36

Pato::Pato(){}

Pato::Pato(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t direccion):
        Entidad(id, pos_x, pos_y),
        armadura_equipada(false),
        casco_equipado(false),
        vivo(true),
        apunta_arriba(false),
        direccion(direccion),
        estado(),
        contador_salto(0),
        contador_caer(0),
        velocidad_caida(3) 
        {
    Arma arma;
    arma.set_se_agarro(false);
    calcular_hitbox();
    // if (color == "rojo") {
    //     this.color = 1;
    // } else if (color == "azul") {
    //     this.color = 2;
    // } else if (color == "verde") {
    //     this.color = 3;
    // } else if (color == "amarillo") {
    //     this.color = 4;
    // } else {
    //     this.color = 0;
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
    pos_y-=10;
    estado.set_saltar();
    contador_salto++;
    if (contador_salto == 5) {
        estado.set_dejar_de_saltar();
        contador_salto = 0;
    }
}

void Pato::aletear() { 
    pos_y++;
    estado.set_aletear(); 
}

void Pato::caer() { 
    if (velocidad_caida == 10 || estado.get_estado_salto() != CAER) {
        velocidad_caida = 3;
    }
    pos_y++;
    estado.set_caer();
    velocidad_caida+=1;
}

void Pato::tomar_arma(Arma nueva_arma) { 
    arma = nueva_arma;
    arma.set_se_agarro(true);
}

void Pato::soltar_arma() { 
    arma.set_se_agarro(false);
    Arma arma; 
}

uint8_t Pato::tiene_arma(){ 
    if (arma.get_se_agarro()){
        return TOMAR_ARMA;
    } else{
        return BYTE_NULO;
    }
}

bool Pato::disparar() {
    if (tiene_arma()) {
        if (arma.disparar()){
            estado.set_disparando();
            return true;
        }
        return false;
    } else {
        estado.set_dejar_de_disparar();
        return false;
        // Si el pato no tiene un arma, no puede disparar
    }
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

void Pato::equipar_armadura() {
    armadura_equipada = true;
}

void Pato::equipar_casco() {
    casco_equipado = true;
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

Arma Pato::get_arma() { return arma; }

bool Pato::esta_vivo() const { return vivo; }

void Pato::morir() { vivo = false; }

// int Pato::get_color() { return color; }

TipoColision Pato::colisiona_con_tile(SDL2pp::Rect hitbox_tile) {
    if (hitbox.no_colisiona(hitbox_tile)) {
        return Nada;
    }
    if (hitbox.colisiona_arriba_con(hitbox_tile)) {
        //std::cout<<"colisiona arriba"<<std::endl;
        return Piso;
    }
    if (hitbox.colisiona_abajo_con(hitbox_tile)) {
        //std::cout<<"colisiona abajo"<<std::endl;
        return Techo;
    }
    if (hitbox.colisiona_izquierda_con(hitbox_tile)) {
        //std::cout<<"colisiona izq"<<std::endl;
        return ParedIzquierda;
    }
    if (hitbox.colisiona_derecha_con(hitbox_tile)) {
        //std::cout<<"colisiona der"<<std::endl;
        return ParedDerecha;
    }
    return Nada;
}

TipoColision Pato::colisiona_con_bala(Bala& bala) {
    HitBox hitbox_bala = bala.get_hitbox();
    if (hitbox.no_colisiona(hitbox_bala.get_hitbox_rect())) {
        return Nada;
    }
    if(bala.get_id_origen() == id){
        return Nada;
    }
    if (hitbox.colisiona_arriba_con(hitbox_bala.get_hitbox_rect()) || hitbox.colisiona_abajo_con(hitbox_bala.get_hitbox_rect()) || hitbox.colisiona_izquierda_con(hitbox_bala.get_hitbox_rect()) || hitbox.colisiona_derecha_con(hitbox_bala.get_hitbox_rect())) {
        return Balas;
    }
    return Nada;
}

TipoColision Pato::colisiona_con_recompensa(HitBox hitbox_caja) {
    
    if (hitbox.no_colisiona(hitbox_caja.get_hitbox_rect())) {
        return Nada;
    }
    if (hitbox.colisiona_arriba_con(hitbox_caja.get_hitbox_rect()) || hitbox.colisiona_abajo_con(hitbox_caja.get_hitbox_rect()) ||hitbox.colisiona_izquierda_con(hitbox_caja.get_hitbox_rect()) || hitbox.colisiona_derecha_con(hitbox_caja.get_hitbox_rect() )) {
        return Recompensas;
    }
    return Nada;
}

void Pato::ajustar_sobre_tile(const SDL2pp::Rect& tile_hitbox) {
    pos_y = tile_hitbox.GetY() - hitbox.get_hitbox_rect().GetH(); 
}

void Pato::ajustar_derecha_tile(const SDL2pp::Rect& tile_hitbox) {
    pos_x = tile_hitbox.GetX() - hitbox.get_hitbox_rect().GetW();
}

void Pato::ajustar_izquierda_tile(const SDL2pp::Rect& tile_hitbox) {
    pos_x = tile_hitbox.GetX() + hitbox.get_hitbox_rect().GetW();
}

void Pato::posicion_pato_muerto(){
    pos_x = 1280;
    pos_y = 720;
}