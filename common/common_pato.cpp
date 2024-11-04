#include "common_pato.h"

#include <iostream>

Pato::Pato(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint8_t direccion):
        Entidad(id, pos_x, pos_y),
        arma(nullptr),
        tomo_armadura(false),
        tomo_casco(false),
        armadura_equipada(false),
        casco_equipado(false),
        vivo(true),
        apunta_arriba(false),
        tirado_al_piso(false),
        direccion(direccion),
        se_mueve_derecha(false) {
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

// Pato::~Pato() { delete arma; }

void Pato::moverse_izquierda() {
    pos_x--;
    direccion = DIRECCION_IZQUIERDA;
}

void Pato::moverse_derecha() {
    pos_x += 1;
    direccion = DIRECCION_DERECHA;
    se_mueve_derecha = true;
}

void Pato::saltar() { pos_y++; }

void Pato::planear() { pos_y--; }

void Pato::tomar_arma(Arma* nuevaArma) { arma = nuevaArma; }

void Pato::soltar_arma() { arma = nullptr; }

void Pato::disparar() {
    if (arma) {
        arma->disparar();
    } else {
        // Si el pato no tiene un arma, no puede disparar
    }
}

void Pato::apuntar_arriba() { apunta_arriba = true; }

void Pato::dejar_de_apuntar_arriba() { apunta_arriba = false; }

bool Pato::esta_apuntando_arriba() { return apunta_arriba; }

void Pato::tirarse_al_piso() {
    tirado_al_piso = true;
}

bool Pato::esta_tirado_al_piso() { return tirado_al_piso; }

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
