#ifndef COMMON_ESTADO_JUEGO_H
#define COMMON_ESTADO_JUEGO_H

#include <cstdint>
#include <list>
#include "common_lobby_info.h"
#include "common_arma.h"
#include "common_bala.h"
#include "common_caja.h"
#include "common_granada.h"
#include "common_pato.h"
#include "common_mapa.h"
#include "common_proteccion.h"

struct EstadoJuego {
    uint8_t informacion_enviada;
    uint8_t partida_iniciada;
    uint16_t id_jugador;
    uint8_t id_partida;
    std::list<uint8_t> partidas;
    Mapa mapa;
    std::list<Pato> patos;
    std::list<Caja> cajas;
    std::list<Arma> armas;
    std::list<Bala> balas;
    std::list<Granada> granadas;
    std::list<Proteccion> armaduras;
    uint16_t ganador_partida;
};

#endif
