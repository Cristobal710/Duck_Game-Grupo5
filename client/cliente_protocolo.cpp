#include "cliente_protocolo.h"

#include <cstring>
#include <iostream>

#include <arpa/inet.h>

#include "../common/common_liberror.h"

ClienteProtocolo::ClienteProtocolo(Socket& socket): Protocolo(socket) {}

void ClienteProtocolo::enviar_comando(ComandoGrafica comando) {
    uint8_t accion = acciones[comando.tecla];
    enviar_byte(accion);
    enviar_byte(comando.jugador_id);
}

void ClienteProtocolo::recibir_pato(std::list<Pato>& patos) {
    bool cerrado;
    uint16_t id = recibir_dos_bytes(cerrado);
    uint16_t pos_x = recibir_dos_bytes(cerrado);
    uint16_t pos_y = recibir_dos_bytes(cerrado);
    uint8_t direccion = recibir_byte(cerrado);
    uint8_t estado_movimiento = recibir_byte(cerrado);
    uint8_t estado_salto = recibir_byte(cerrado);
    uint16_t apunta_arriba = recibir_byte(cerrado);
    uint16_t estado_agachado = recibir_byte(cerrado);
    uint16_t esta_vivo = recibir_byte(cerrado);
    uint16_t casco_inventario = recibir_dos_bytes(cerrado);
    uint16_t armadura_inventario = recibir_dos_bytes(cerrado);
    uint16_t casco_equipado = recibir_dos_bytes(cerrado);
    uint16_t armadura_equipada = recibir_dos_bytes(cerrado);
    // uint8_t arma_id = recibir_byte(cerrado);
    // uint8_t municion_disponible = recibir_byte(cerrado);

    Pato pato(id, pos_x, pos_y, direccion);
    pato.estado = EstadoPato(estado_movimiento, estado_salto, estado_agachado);
    if (static_cast<bool>(apunta_arriba)) {
        pato.apuntar_arriba();
    }
    if (static_cast<bool>(casco_inventario)) {
        pato.tomar_casco();
    }
    if (static_cast<bool>(armadura_inventario)) {
        pato.tomar_armadura();
    }
    if (static_cast<bool>(casco_equipado)) {
        pato.equipar_casco();
    }
    if (static_cast<bool>(armadura_equipada)) {
        pato.equipar_armadura();
    }
    if (!(static_cast<bool>(esta_vivo))) {
        pato.morir();
    }

    //Arma arma(arma_id, pos_x, pos_y, municion_disponible, 30, 10);

    //pato.tomar_arma(&arma);
    patos.push_back(pato);
}

std::list<Pato> ClienteProtocolo::recibir_patos() {
    std::list<Pato> patos;
    std::vector<uint8_t> cantidad_patos(2);
    bool cerrado;
    socket.recvall(cantidad_patos.data(), cantidad_patos.size(), &cerrado);
    int cantidad = static_cast<int>(cantidad_patos[1]);

    for (int i = 0; i < cantidad; i++) {
        recibir_pato(patos);
    }
    return patos;
}


void ClienteProtocolo::recibir_caja(std::list<Caja>& cajas) {
    bool cerrado;
    uint16_t id = recibir_dos_bytes(cerrado);
    uint16_t pos_x = recibir_dos_bytes(cerrado);
    uint16_t pos_y = recibir_dos_bytes(cerrado);
    uint8_t recompensa_id = recibir_byte(cerrado);
    Caja caja(id, pos_x, pos_y, recompensa_id);
    cajas.push_back(caja);
}


std::list<Caja> ClienteProtocolo::recibir_cajas() {
    std::list<Caja> cajas;
    std::vector<uint8_t> cantidad_patos(2);
    bool cerrado;
    socket.recvall(cantidad_patos.data(), cantidad_patos.size(), &cerrado);
    int cantidad = static_cast<int>(cantidad_patos[1]);

    for (int i = 0; i < cantidad; i++) {
        recibir_caja(cajas);
    }
    return cajas;
}

void ClienteProtocolo::recibir_arma(std::list<Arma>& armas) {
    bool cerrado;
    uint8_t id = recibir_byte(cerrado);
    uint8_t pos_x = recibir_byte(cerrado);
    uint8_t pos_y = recibir_byte(cerrado);
    uint8_t alcance = recibir_byte(cerrado);
    uint8_t municion_disponible = recibir_byte(cerrado);
    uint8_t balas_max = recibir_byte(cerrado);
    Arma arma(id, pos_x, pos_y, alcance, municion_disponible, balas_max);
    armas.push_back(arma);
}

std::list<Arma> ClienteProtocolo::recibir_armas() {
    std::list<Arma> armas;
    std::vector<uint8_t> cantidad_armas(2);
    bool cerrado;
    socket.recvall(cantidad_armas.data(), cantidad_armas.size(), &cerrado);
    int cantidad = static_cast<int>(cantidad_armas[1]);

    for (int i = 0; i < cantidad; i++) {
        recibir_arma(armas);
    }
    return armas;
}


void ClienteProtocolo::recibir_bala(std::list<Bala>& balas) {
    bool cerrado;
    uint16_t id = recibir_dos_bytes(cerrado);
    uint16_t pos_x = recibir_dos_bytes(cerrado);
    uint16_t pos_y = recibir_dos_bytes(cerrado);
    uint16_t pos_x_final = recibir_dos_bytes(cerrado);
    uint16_t pos_y_final = recibir_dos_bytes(cerrado);
    uint8_t direccion = recibir_byte(cerrado);

    Bala bala(id, pos_x, pos_y, pos_x_final, pos_y_final, direccion);
    balas.push_back(bala);
}

std::list<Bala> ClienteProtocolo::recibir_balas() {
    std::list<Bala> balas;
    std::vector<uint8_t> cantidad_balas(2);
    bool cerrado;
    socket.recvall(cantidad_balas.data(), cantidad_balas.size(), &cerrado);
    int cantidad = static_cast<int>(cantidad_balas[1]);

    for (int i = 0; i < cantidad; i++) {
        recibir_bala(balas);
    }
    return balas;
}

void ClienteProtocolo::recibir_granada(std::list<Granada>& granadas) {
    bool cerrado;
    uint8_t id = recibir_byte(cerrado);
    uint8_t pos_x = recibir_byte(cerrado);
    uint8_t pos_y = recibir_byte(cerrado);
    uint8_t rango = recibir_byte(cerrado);
    uint8_t activa = recibir_byte(cerrado);
    uint8_t exploto = recibir_byte(cerrado);

    Granada granada(id, pos_x, pos_y, rango);
    if (static_cast<bool>(activa)) {
        granada.activar();
    }
    if (static_cast<bool>(exploto)) {
        granada.explotar();
    }
    granadas.push_back(granada);
}

std::list<Granada> ClienteProtocolo::recibir_granadas() {
    std::list<Granada> granadas;
    std::vector<uint8_t> cantidad_granadas(2);
    bool cerrado;
    socket.recvall(cantidad_granadas.data(), cantidad_granadas.size(), &cerrado);
    int cantidad = static_cast<int>(cantidad_granadas[1]);

    for (int i = 0; i < cantidad; i++) {
        recibir_granada(granadas);
    }
    return granadas;
}


EstadoJuego ClienteProtocolo::recibir_estado_juego() {
    EstadoJuego estado_juego;
    estado_juego.patos = recibir_patos();
    // estado_juego.cajas = recibir_cajas();
    // estado_juego.armas = recibir_armas();
    return estado_juego;
}
