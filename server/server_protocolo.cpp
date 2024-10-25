#include "server_protocolo.h"

#define EXITO 0
#define ERROR 1

ServerProtocolo::ServerProtocolo(Socket& skt): Protocolo(skt) {}

EventoServer ServerProtocolo::recibir_evento() {
    bool cerrado = false;
    EventoServer evento;
    evento.accion = recibir_byte(cerrado);
    evento.jugador_id = recibir_byte(cerrado);
    return evento;
}

void ServerProtocolo::enviar_estado_juego(EstadoJuego& estado) {
    std::cout << estado.estado.size() << std::endl;
    // enviar_byte(estado.jugadores.size());
    // // tambien enviar
    // for (auto& jugador : estado.jugadores) {
    //     enviar_byte(jugador.id);
    //     enviar_byte(jugador.pos_x);
    //     enviar_byte(jugador.pos_y);
    //     enviar_byte(jugador.apunta_arriba);
    //     enviar_byte(jugador.esta_vivo);
    //     enviar_byte(jugador.arma->id);
    //     enviar_byte(jugador.arma->balas);
    //     enviar_byte(jugador.arma->id);
    //     enviar_byte(jugador.arma->balas);
    //     enviar_byte(jugador.arma->id);
    //     enviar_byte(jugador.arma->balas);
    //     enviar_byte(jugador.arma->id);
    //     enviar_byte(jugador.arma->balas);
    //     enviar_byte(jugador.arma->id);
    //     enviar_byte(jugador.arma->balas);
    //     enviar_byte(jugador.arma->id);
    //     enviar_byte(jugador.arma->balas);
    //     enviar_byte(jugador.arma->id);
    //     enviar_byte(jugador.arma->balas);
    //     enviar_byte(jugador.arma->id);
    //     enviar_byte(jugador.arma->balas);
    //     enviar_byte(jugador.arma->id);
    //     enviar_byte(jugador.arma->balas);
    //     enviar_byte(jugador.arma->id);
    //     enviar_byte(jugador.arma->balas);
    // }
    // enviar_byte(estado.cajas.size());
    // for (auto& caja : estado.cajas) {
    //     enviar_byte(caja.id);
    //     enviar_byte(caja.pos_x);
    //     enviar_byte(caja.pos_y);
    // }
    // enviar_byte(estado.recompensas.size());
    // for (auto& recompensa : estado.recompensas) {
    //     enviar_byte(recompensa.id);
    //     enviar_byte(recompensa.pos_x);
    //     enviar_byte(recompensa.pos_y);
    //     enviar_byte(recompensa.tipo);
    // }
    // enviar_byte(estado.balas.size());
    // for (auto& bala : estado.balas) {
    //     enviar_byte(bala.id);
    //     enviar_byte(bala.pos_x);
    //     enviar_byte(bala.pos_y);
    //     enviar_byte(bala.direccion);
    // }
    // enviar_byte(estado.explosiones.size());
    // for (auto& explosion : estado.explosiones) {
    //     enviar_byte(explosion.id);
    // }
}
