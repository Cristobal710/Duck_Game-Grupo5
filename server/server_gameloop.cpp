#include "server_gameloop.h"

#include "../common/common_constantes.h"

#define BAZOOKA "Bazooka"
#define CHAINSAW "Chainsaw"
#define DEATH_RAY "Death ray"
#define SHOTGUN "Shotgun"

GameLoop::GameLoop(Queue<EstadoJuego>& cola_estados_juego,
        bool* conexion):
        mapa_clientes(),
        clientes(mapa_clientes),
        cola_estados_juego(cola_estados_juego),
        esta_cerrado(conexion) {
        ultimo_estado = EstadoJuego();
        }


// void GameLoop::cerrar_gameloop() {
//     cola_eventos.close();
//     clientes.cerrar_gameloop();
//     _is_alive = false;
// }

// void GameLoop::eliminar_clientes_cerrados() {
//     clientes.eliminar_clientes_cerrados();
// }

void GameLoop::agregar_cliente(ServerClient& cliente, Queue<EventoServer>& cola_cliente) {
    clientes.agregar_cliente(cliente, cola_cliente);
}

void GameLoop::procesar_evento(EventoServer& evento, EstadoJuego& estado_juego) {
    for (Pato& pato: estado_juego.patos) {
        if (pato.get_id() == evento.jugador_id) {
            ejecutar_accion(evento.accion, pato);
        }
    }
}

void GameLoop::ejecutar_accion(uint8_t accion, Pato& pato) {
    switch (accion) {
        case MOVER_IZQUIERDA:
            pato.moverse_izquierda();
            break;
        case MOVER_DERECHA:
            pato.moverse_derecha();
            break;
        case TIRAR_PISO:
            pato.tirarse_al_piso();
            break;
        case APUNTAR_ARRIBA:
            pato.apuntar_arriba();
            break;
        case SALTAR_ALETEAR:
            pato.saltar();
            break;
        case TOMAR_ARMA:
            // llamar a un metodo que recorra el array de armas y devuelva la cercana al pato
            // pato.tomar_arma();
            break;
        default:
            // hacer metodo que ponga quieto al pato
            pato.estado.set_dejar_de_moverse();
            pato.levantarse_del_piso();
            break;

    }
}

// void GameLoop::enviar_estado_juego_si_cambio(Pato& pato, EstadoJuego& estado_anterior) {
//     if (pato.estado.get_estado_agachado() != estado_anterior.patos.front().estado.get_estado_agachado() || pato.estado.get_estado_movimiento() != estado_anterior.patos.front().estado.get_estado_movimiento()) {
//         std::cout << "cambio" << std::endl;
//         cola_estados_juego.push(ultimo_estado);
//     }
// }

void GameLoop::run() {
    Pato pato(3, 0, 0, 0);
    ultimo_estado.patos.emplace_back(pato);

    while (!(*esta_cerrado)) {
        //eliminar_clientes_cerrados();
     
        while (true) {
            EstadoJuego estado_anterior = ultimo_estado;
            std::vector<EventoServer> eventos = clientes.recibir_mensajes_clientes();
            if (eventos.empty()) {
                for (Pato& pato: ultimo_estado.patos) {
                    pato.estado.set_dejar_de_moverse();
                    pato.estado.set_dejar_de_agacharse();
                    //enviar_estado_juego_si_cambio(pato, estado_anterior);
                }
            }
            for(EventoServer evento : eventos){
                procesar_evento(evento, ultimo_estado);
                cola_estados_juego.push(ultimo_estado);
            }
            for (Pato& pato: ultimo_estado.patos) {
                if (pato.estado.get_estado_salto() == SALTAR_ALETEAR) {
                    pato.saltar();
                    // cola_estados_juego.push(ultimo_estado);
                }
            }
            // enviar_estado_juego_si_cambio(pato, estado_anterior);
            // aplicar logica del juego, balas, gravedad, etc
            // pushear
            // sleep
        }
    }

    //cerrar_gameloop();
}
