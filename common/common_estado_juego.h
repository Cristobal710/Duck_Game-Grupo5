#ifndef COMMON_ESTADO_JUEGO_H
#define COMMON_ESTADO_JUEGO_H

#include <cstdint>
#include <list>
#include "common_pato.h"
#include "common_caja.h"
#include "common_arma.h"
#include "common_bala.h"
#include "common_granada.h"


struct EstadoJuego {
    std::list<Pato> patos;
    std::list<Caja> cajas;
    std::list<Arma> armas;
    std::list<Bala> balas;
    std::list<Granada> granadas;
};

#endif
