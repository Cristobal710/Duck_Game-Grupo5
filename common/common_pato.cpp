#include "common_pato.h"
#include <iostream>

Pato::Pato(const std::string& color, int x, int y) : id(id), pos_x(x), pos_y(y), arma(nullptr), vivo(true), armadura_equipada(false), casco_equipado(false) {}

Pato::~Pato() {
    delete arma;
}

void Pato::moverse_izquierda() {
    pos_x--;
}

void Pato::moverse_derecha() {
    pos_x++;
}

void Pato::saltar() {
    pos_y++;
}

void Pato::planear() {
    pos_y--;
}

void Pato::tomar_arma(Arma* nuevaArma) {
    arma = nuevaArma;
}

void Pato::soltar_arma() {
    arma = nullptr;
}

void Pato::disparar() {
    if (arma) {
        arma->disparar();
    } else {
        // Si el pato no tiene un arma, no puede disparar
    }
}

void Pato::apuntar_arriba() {
    apunta_arriba = true;
}

void Pato::dejar_de_apuntar_arriba() {
    apunta_arriba = false;
}

void Pato::tirarse_al_piso() {
    // esto deberia avisar al server y de alguna manera haga la animacion
}

void Pato::tomar_armadura() {
    tomo_armadura = true;
}

void Pato::tomar_casco() {
    tomo_casco = true;
}

void Pato::equipar_armadura() {
    if (tomo_armadura){
        armadura_equipada = true;
    }
}

void Pato::equipar_casco() {
    if (tomo_casco){
        casco_equipado = true;
    }
}

void Pato::recibir_danio() {   
    // En caso de que el pato solo aguante una bala, entonces hay que hacer que el pato muera
    // sino tiene armadura o casco
    if (armadura_equipada){
        armadura_equipada = false;
        tomo_armadura = false;
        return;
    }
    if (casco_equipado){
        casco_equipado = false;
        tomo_casco = false;
        return;
    } 
    morir();
}

bool Pato::esta_vivo() const {
    return vivo;
}

void Pato::morir() {
    vivo = false;
}