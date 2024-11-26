#ifndef COMMON_PEDIDO_JUGADOR_H   
#define COMMON_PEDIDO_JUGADOR_H  
#include "../common/common_constantes.h"
#include <cstdint>

class PedidoJugador {
    private:
    
    public:
    PedidoJugador();
    uint8_t crear_partida;
    uint8_t unirse_a_partida;
    uint8_t id_partida_a_unirse;
    uint8_t un_jugador;
    uint8_t dos_jugadores;
    void partida_nueva();
    void unirse_a_partida_con_id(uint8_t id_partida);
    void juega_uno_solo();
    void juegan_dos_personas();
};


#endif
