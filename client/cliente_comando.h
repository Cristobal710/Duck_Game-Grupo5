#ifndef CLIENTE_COMANDO_h
#define CLIENTE_COMANDO_h
#include <cstdint>
#include <string>
#include "../common/common_pedido_jugador.h"

struct ComandoGrafica {
    std::string tecla;
    uint8_t jugador_id;
    PedidoJugador pedido;
};


#endif
