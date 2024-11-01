#include "server_gameloop.h"

#include "../common/common_constantes.h"

#define CAJA_NUEVA "A new box has appeared"

#define BAZOOKA_NUEVA 15
#define CHAINSAW_NUEVA 5
#define DEATH_RAY_NUEVA 20
#define SHOTGUN_NUEVA 10

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
            pato.se_mueve_derecha = false;
            break;

    }
}

void GameLoop::run() {
    Pato pato(3, 0, 0, 0);
    ultimo_estado.patos.emplace_back(pato);

    while (!(*esta_cerrado)) {
        //eliminar_clientes_cerrados();
     
        while (true) {
            std::vector<EventoServer> eventos = clientes.recibir_mensajes_clientes();
            if (eventos.empty()) {
                pato.se_mueve_derecha = false;
            }
            for(EventoServer evento : eventos){
                procesar_evento(evento, ultimo_estado);
                cola_estados_juego.push(ultimo_estado);
            }
        }
    }

    //cerrar_gameloop();
}
