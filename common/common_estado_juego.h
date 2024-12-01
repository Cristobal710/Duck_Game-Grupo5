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


struct EstadoJuego {
    std::list<uint16_t> ids_tomados;
    uint8_t id_partida;
    std::list<uint8_t> partidas;
    LobbyInfo lobby_data;
    Mapa mapa;
    std::list<Pato> patos;
    std::list<Caja> cajas;
    std::list<Arma> armas;
    std::list<Bala> balas;
    std::list<Granada> granadas;
};

#endif
