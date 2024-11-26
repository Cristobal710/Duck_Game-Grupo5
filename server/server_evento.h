#ifndef SERVER_EVENTO_H
#define SERVER_EVENTO_H
struct EventoServer {
    uint8_t accion;
    uint8_t jugador_id;
    PedidoJugador pedido;
};


#endif
